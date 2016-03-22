# copyright 2016 Apache 2 sddekit authors

"""
This module helps build the preprocessed header
file for use with pycparser, using its fake stdlib
headers.

"""

import pycparser

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