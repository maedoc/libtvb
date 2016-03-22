# copyright 2016 Apache 2 sddekit authors

import build

def main(argv):
    task = argv[1]

    if task == 'build':
        object_files = build.build_objects()
        build.assemble_shared_lib(object_files)
        build.build_benchmarks(object_files)

    elif task == 'clean':
        build.clean()