# copyright 2016 Apache 2 sddekit authors

"""
This module helps with certain development tasks related to
SDDEKit, such as building the shared library with CMake
and generating binding code for higher-level languages.

Currently the supported workflow is as follows

- cmake_configure()
- cmake_build()
- generate a preprocessed_header()
- generate_fn_ptr_field_wrapper_files()

though the intention is to support

- generation of ctypes Structure subclasses and suitable function signatures
- generation of default Python classes to wrap structures (

"""

import io
import os
import sys
from os.path import exists, join, abspath
import subprocess
import ctypes
import pycparser
from pycparser import c_ast

HERE = os.path.dirname(os.path.abspath(__file__))
UP = os.path.dirname(HERE)

# preprocess simple header {{{

def get_fake_libc_include_path():
    "Find fake libc or download it from GitHub."
    if exists(join(HERE, 'pycparser-master')):
        os.environ['PYCPARSER'] = join(HERE, 'pycparser-master')
    if 'PYCPARSER' not in os.environ:
        if '-y' not in sys.argv:
            yn = raw_input("fake libc includes required from pycparser, download? [y/N]")
        else:
            sys.argv.remove('-y')
            yn = 'y'
        if yn in ('y', 'Y'):
            import urllib, zipfile
            url = 'https://github.com/eliben/pycparser/archive/master.zip'
            tmp, _ = urllib.urlretrieve(url)
            zipfile.ZipFile(tmp).extractall()
            os.environ['PYCPARSER'] = HERE
        else:
            print ("Please download pycparser source from "
                   "https://github.com/eliben/pycparser "
                   "and provide path as environment variable PYCPARSER=/path/to.")
    libc = None
    if 'PYCPARSER' in os.environ:
        libc = abspath(join(os.environ['PYCPARSER'], 'utils', 'fake_libc_include'))
    import pdb; pdb.set_trace()
    return libc

def build_cpp_cmd(header='sddekit_simple.h', cc='gcc', libc=None):
    "Build command list for preprocessing the header file."
    cmd = [os.environ.get('CC', cc), '-nostdinc']
    libc = libc or get_fake_libc_include_path()
    if libc:
        cmd.append('-I%s' % (libc, ))
    cmd += ['-E', join(UP, 'src', header)]
    return cmd

PPFNAME = 'sddekit_simple_pp.h'

def preprocessed_header(cmd=None, redo=False, ppfname=PPFNAME):
    "Preprocess header and return resulting string."
    if exists(join(HERE, ppfname)) and not redo:
        with open(ppfname, 'r') as fd:
            header = fd.read()
    else:
        cmd = cmd or build_cpp_cmd()
        print (cmd)
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        proc.wait()
        header = proc.stdout.read().decode('utf-8').replace('\r', '')
        with open('sddekit_simple_pp.h', 'w') as fd:
            fd.write(header)
    return header

def header_ast(src=None, ppfname=PPFNAME):
    src = src or preprocessed_header()
    cp = pycparser.CParser()
    ast = cp.parse(src, ppfname)
    return ast

# preprocess simple header }}}

# ast vistors {{{

class App(c_ast.NodeVisitor):
    """
    Subclass of NodeVisitor with simple class method to build instance,
    visit a given node, and return instance.

    """

    @classmethod
    def apply(cls, node):
        obj = cls()
        obj.visit(node)
        return obj


class TypeInfo(App):
    "Visits a type to extract it's pointer level, declaration name and type."

    def __init__(self):
        self.ptr = 0
        self.name = ''
        self.typenames = ''

    def visit_PtrDecl(self, node):
        self.ptr += 1
        self.generic_visit(node)

    def visit_TypeDecl(self, node):
        self.name = node.declname
        self.generic_visit(node)

    def visit_IdentifierType(self, node):
        self.typenames = ' '.join(node.names)


class FuncInfo(App):
    "Visits a function declaration to extract name, result and argument types."

    def __init__(self):
        self.restype = None
        self.name = ''
        self.argtypes = []

    def visit_FuncDecl(self, node):
        self.restype = TypeInfo.apply(node.type)
        self.name = self.restype.name
        self.argtypes = [TypeInfo.apply(child) for _, child in node.args.children()]


class VisitStructFnPtrFields(App):
    """
    Visits function pointers which are fields of structs.

    This will not do anything by itself, but should probably be subclassed
    with a visit_FuncDecl method to do something with the resulting
    function pointer declarations.

    """

    def __init__(self):
        self.struct = 0
        self.ptr = 0
        self.typedef = False
        self.struct_name = []

    def visit_Typedef(self, node):
        self.typedef = True
        self.generic_visit(node)
        self.typedef = False

    def visit_PtrDecl(self, node):
        self.ptr += 1
        self.generic_visit(node)
        self.ptr -= 1

    def visit_Struct(self, node):
        self.struct += 1
        self.struct_name.append(node.name)
        if not self.typedef:
            self.generic_visit(node)
        self.struct_name.pop()
        self.struct -= 1


class GenFnPtrFieldWrappers(VisitStructFnPtrFields):
    """
    Visits function pointer in struct declarations to extract
    type and name information in order to generate header and implementation
    of regular functions which wrap the function pointer.

    """

    _h_template = "{restype} {struct_name}_{field_name}({arg_types});\n"

    _c_template = "{restype} {struct_name}_{field_name}({arg_type_names})\n{{\n\treturn {first_arg}->{field_name}({arg_names});\n}}\n\n"

    def __init__(self):
        super(GenFnPtrFieldWrappers, self).__init__()
        self.header_lines = []
        self.source_lines = []

    def visit_FuncDecl(self, node):
        if self.struct and self.ptr:
            fi = FuncInfo.apply(node)
            arg_names, arg_types = [], []
            for i, arg in enumerate(fi.argtypes):
                arg_names.append('a%d' % (i, ))
                arg_types.append(arg.typenames + ('*' * arg.ptr))
            data = {
                'restype': fi.restype.typenames + ('*' * fi.restype.ptr),
                'struct_name': self.struct_name[-1],
                'field_name': fi.name,
                'arg_types': ', '.join(arg_types),
                'arg_names': ', '.join(arg_names),
                'arg_type_names': ', '.join('%s %s' % (t, n) for n, t in zip(arg_names, arg_types)),
                'first_arg': arg_names[0],
            }
            self.header_lines.append(self._h_template.format(**data))
            self.source_lines.append(self._c_template.format(**data))

# ast visitors }}}

def generate_fn_ptr_field_wrapper_files(path=None, redo=False, filename='fn_ptr_field_wrappers'):
    """
    Generates a header and source file containing regular functions wrapping
    all struct fields which are function pointers.

    Parameters
    ----------
    path : string
        Path to write files to.
    filename : string
        Name to give header and source files.

    """
    import api
    path = path or './'
    hpath = join(path, filename + '.h')
    cpath = hpath[:-1] + 'c'
    if exists(hpath) and exists(cpath) and redo is False:
        return
    wrappers = GenFnPtrFieldWrappers.apply(api.header_ast())
    with open(hpath, 'w') as fd:
        fd.write('''/* copyright 2016 Apache 2 sddekit authors */\n
/* This file was automatically generated based on src/sddekit_simple.h */\n
''')
        for line in wrappers.header_lines:
            fd.write(line)

    with open(cpath, 'w') as fd:
        fd.write('''/* copyright 2016 Apache 2 sddekit authors */\n
/* This file was automatically generated based on src/sddekit_simple.h */\n
#include "sddekit.h"\n
''')
        for line in wrappers.source_lines:
            fd.write(line)

# build shared lib

build_dir = os.path.join(HERE, 'lib', 'build')

def cmake_configure(redo):
    if not os.path.exists(build_dir):
        echo "build directory (%r) doesn't exist, making" % (build_dir, )
        os.mkdir(build_dir)
    proc = subprocess.Popen(['cmake', '..'], cwd=build_dir)
    proc.wait()

def cmake_build(redo):
    if not os.path.exists(build_dir):
        print 'build dir not found, configuring first..'
        cmake_configure(redo)
    proc = subprocess.Popen(['make'], cwd=build_dir)
    proc.wait()

def cmake_clean(redo):
    if not os.path.exists(build_dir):
        print 'build dir not found, configuring first..'
        cmake_configure()
    proc = subprocess.Popen(['make', 'clean'], cwd=build_dir)
    proc.wait()
    print ('done')

def gh_pages(redo):
    """
	git branch -D gh-pages
	git init docs
	doxygen
	cd docs && git add html/* && git mv html/* ./ && git commit -m "add doxygen html"
	git fetch docs master:gh-pages
	rm -rf docs
    """

if __name__ == '__main__':
    allcmds = ['generate_fn_ptr_field_wrapper_files', 'preprocessed_header',
               'cmake_build', 'cmake_configure', 'cmake_clean']
    cmds = sys.argv[1:]
    if len(cmds) == 0 or any(cmd not in allcmds for cmd in cmds):
        print ('usage: python api.py <cmd> [<cmd> ...]')
        print ('where <cmd> is one of %r' % (allcmds,))
    else:
        for cmd in sys.argv[1:]:
            eval(cmd)(redo=True)
