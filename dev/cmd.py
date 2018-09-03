# copyright 2016 Apache 2 libtvb authors

import dev.build

def main(argv):
    task = argv[1]

    if task == 'build':
        object_files = dev.build.build_objects()
        dev.build.assemble_shared_lib(object_files)
        dev.build.build_benchmarks(object_files)

    elif task == 'clean':
        dev.build.clean()
    
    elif task == 'execfile':
        import sys, subprocess, os
        env = os.environ.copy()
        env['PYTHONPATH'] = './'
        subprocess.Popen([sys.executable, argv[2]], env=env).wait()
