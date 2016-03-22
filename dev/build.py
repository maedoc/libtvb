# copyright 2016 Apache 2 sddekit authors

import sys
import os
import os.path
import shutil
import subprocess
import multiprocessing
import logging

LOG = logging.getLogger(__name__)

def configure():
    includes = ['-Ilib/include']
    
    compile = {
        '.c': ['gcc', '-std=c99'] + includes,
        '.cpp': ['g++'] + includes
    }
    
    def append_flags(*flags):
        for flag in flags:
            compile['.c'].append(flag)
            compile['.cpp'].append(flag)
            
    dll_ext = '.so'
    
    if sys.platform != 'win32':
        append_flags('-fPIC')
    else:
        dll_ext = '.dll'

    if sys.platform == 'darwin':
        dll_ext = '.dylib'

    if '-g' in sys.argv:
        append_flags('-g', '-Wall', '-Wextra')
    else:
        append_flags('-O3')#, '-flto')

    if '-pg' in sys.argv:
        append_flags('-pg')

    # directory for build artifacts
    build_dir = 'build'
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    return includes, compile, dll_ext, build_dir

INCLUDES, COMPILE, DLL_EXT, BUILD_DIR = configure()

def sh(cmd):
    LOG.info(' '.join(cmd))
    subprocess.check_call(cmd)

def compile_file(source_file, debug=False):
    name, ext = os.path.splitext(source_file)
    cmd = COMPILE[ext][:]
    obj_file = os.path.join(BUILD_DIR, 
        '_'.join(name.split(os.path.sep)[2:]) + '.o')
    cmd += ['-c', source_file, '-o', obj_file]
    sh(cmd)
    return obj_file

def assemble_shared_lib(object_files):
    cmd = COMPILE['.c'] + ['-shared', '-lm']
    cmd += object_files
    cmd += ['-o', os.path.join(BUILD_DIR, 'libSDDEKit') + DLL_EXT]
    sh(cmd)
    
def source_files():
    path = os.path.join('lib', 'src')
    for root, folders, files in os.walk(path):
        for file in files:
            name, ext = os.path.splitext(file)
            if ext in ('.c', '.cpp'):
                yield os.path.join(root, file)

def build_objects(parallel=False):
    sources = list(source_files())
    if parallel:
        pool = multiprocessing.Pool()
        object_files = pool.map(compile_file, sources)
        pool.close()
    else:
        object_files = list(map(compile_file, sources))
    return object_files

def build_benchmarks(object_files, use_shared=False):
    benchmarks = ['bench_net_gen2d']
    for benchmark in benchmarks:
        source = os.path.join('lib', 'bench', benchmark)
        cmd = COMPILE['.c'][:]
        if use_shared:
            cmd += ['-L' + os.path.abspath(BUILD_DIR), '-lSDDEKit']
        else:
            cmd += object_files
        cmd += [source + '.c', '-lm', '-o', os.path.join(BUILD_DIR, benchmark)]
        sh(cmd)

def clean():
    shutil.rmtree(BUILD_DIR)
 
def gh_pages(redo):
    """
	git branch -D gh-pages
	git init docs
	doxygen
	cd docs && git add html/* && git mv html/* ./ && git commit -m "add doxygen html"
	git fetch docs master:gh-pages
	rm -rf docs
    """
   
