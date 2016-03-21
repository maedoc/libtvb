import sys
import os
import os.path
import tempfile
import subprocess
import multiprocessing

HERE = os.path.dirname(os.path.abspath(__file__))

INCLUDES = ['-Ilib/include']

COMPILE = {
    '.c': ['gcc', '-std=c99'] + INCLUDES,
    '.cpp': ['g++'] + INCLUDES
}

def append_flags(*flags):
    for flag in flags:
        COMPILE['.c'].append(flag)
        COMPILE['.cpp'].append(flag)

DLL_EXT = '.so'

if sys.platform != 'win32':
    append_flags('-fPIC')
else:
    DLL_EXT = '.dll'

if sys.platform == 'darwin':
    DLL_EXT = '.dylib'

if '-g' in sys.argv:
    append_flags('-g')
else:
    append_flags('-O3')

if '-pg' in sys.argv:
    append_flags('-pg')

KEEP_OBJ = '-g' in sys.argv or '-pg' in sys.argv

def sh(cmd):
    print ' '.join(cmd)
    subprocess.check_call(cmd)

def compile_file(source_file, debug=False):
    cmd = COMPILE[os.path.splitext(source_file)[1]][:]
    obj_file = tempfile.NamedTemporaryFile(suffix='.o', delete=False)
    if debug:
        cmd.append('-g')
    cmd += ['-c', source_file, '-o', obj_file.name]
    sh(cmd)
    return obj_file.name

def assemble_shared_lib(object_files):
    sh(COMPILE['.c'] + ['-shared', '-lm'] + object_files + ['-o', 'libSDDEKit' + DLL_EXT])
    if not KEEP_OBJ:
        for file_name in object_files:
            os.remove(file_name)
    
def source_files():
    path = os.path.join(HERE, 'lib', 'src' + os.path.sep)
    for root, folders, files in os.walk(path):
        for file in files:
            name, ext = os.path.splitext(file)
            if ext in ('.c', '.cpp'):
                yield os.path.join(root, file)

def build_shared_lib():
    obj_files = []
    pool = multiprocessing.Pool()
    obj_files = pool.map(compile_file, list(source_files()))
    pool.close()
    assemble_shared_lib(obj_files)

def build_benchmarks():
    benchmarks = ['bench_net_gen2d']
    for benchmark in benchmarks:
        source = os.path.join(HERE, 'lib', 'bench', benchmark)
        cmd = COMPILE['.c'] + ['-L./', '-lSDDEKit']
        cmd += [source + '.c', '-o', benchmark]
        sh(cmd)
    
if __name__ == '__main__':
    build_shared_lib()
    build_benchmarks()
