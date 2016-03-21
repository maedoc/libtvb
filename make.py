import sys
import os
import os.path
import tempfile
import subprocess

HERE = os.path.dirname(os.path.abspath(__file__))

INCLUDES = ['-Ilib/include']

COMPILE = {
    '.c': ['gcc', '-std=c99'] + ['-Ilib/include'],
    '.cpp': ['g++'] + ['-Ilib/include']
}

DLL_EXT = '.so'

if sys.platform != 'win32':
    COMPILE['.c'].append('-fPIC')
    COMPILE['.cpp'].append('-fPIC')
    DLL_EXT = '.dll'

if sys.platform == 'darwin':
    DLL_EXT = '.dylib'

def compile_file(source_file):
    cmd = COMPILE[os.path.splitext(source_file)[1]][:]
    cmd += ['-Ilib/include']
    obj_file = tempfile.NamedTemporaryFile(suffix='.o')
    cmd += ['-c', source_file, '-o', obj_file.name]
    proc = subprocess.check_call(cmd)
    return obj_file

def assemble_shared_lib(object_files):
    names = [file.name for file in object_files]
    cmd = ['gcc', '-shared', '-lm'] + names + ['-o', 'libSDDEKit.so']
    proc = subprocess.check_call(cmd)
    
def source_files():
    path = os.path.join(HERE, 'lib', 'src' + os.path.sep)
    for root, folders, files in os.walk(path):
        for file in files:
            name, ext = os.path.splitext(file)
            if ext in ('.c', '.cpp'):
                yield os.path.join(root, file)

def build_shared_lib():
    obj_files = []
    for file in source_files():
        obj_files.append(compile_file(file))
    assemble_shared_lib(obj_files)
    
if __name__ == '__main__':
    build_shared_lib()