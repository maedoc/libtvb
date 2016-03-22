# copyright 2016 Apache 2 sddekit authors

"""
This module implements visitors for extracting SDDEKit's API
from pycparser's parse tree of SDDEKit's header.

"""

import pycparser

class BaseVisitor(pycparser.c_ast.NodeVisitor):
    """
    Subclass of NodeVisitor with simple class method to build instance,
    visit a given node, and return instance.

    """

    @classmethod
    def apply(cls, node):
        obj = cls()
        obj.visit(node)
        return obj


class TypeInfo(BaseVisitor):
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


class FuncInfo(BaseVisitor):
    "Visits a function declaration to extract name, result and argument types."

    def __init__(self):
        self.restype = None
        self.name = ''
        self.argtypes = []

    def visit_FuncDecl(self, node):
        self.restype = TypeInfo.apply(node.type)
        self.name = self.restype.name
        self.argtypes = [TypeInfo.apply(child) for _, child in node.args.children()]


class VisitStructFnPtrFields(BaseVisitor):
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
    license = ''
    with open('LICENSE', 'r') as fd:
        license = fd.readline().strip()
    with open(hpath, 'w') as fd:
        fd.write('/* {license} */\n\n')
        for line in wrappers.header_lines:
            fd.write(line)
    with open(cpath, 'w') as fd:
        fd.write('''/* copyright 2016 Apache 2 sddekit authors */\n
/* This file was automatically generated based on src/sddekit_simple.h */\n
#include "sddekit.h"\n
''')
        for line in wrappers.source_lines:
            fd.write(line)


class Enums(BaseVisitor):

	def __init__(self):
		self.enums = {}

	def visit_Enum(self, node):
		self.enums[node.name] = []
		(_, elist), = node.children()
		for _, val in elist.children():
			self.enums[node.name].append(val.name)

class Structs(VisitStructFields):

	def __init__(self):
		super(Structs, self).__init__()
		self.structs = {}

	def _add_field(self, field, replace_last=False):
		struct_name = self.struct_name[-1]
		if struct_name not in self.structs:
			self.structs[struct_name] = []
		self.structs[struct_name].append(field)

	def visit_FuncDecl(self, node):
		if self.struct:
			self._add_field(api.FuncInfo.apply(node))