# copyright 2016 Apache 2 sddekit authors

"""
This module helps build the preprocessed header
file for use with pycparser, using its fake stdlib
headers.

"""

import os.path
import logging
import subprocess
import pycparser
import dev.build

LOG = logging.getLogger(__name__)

def build_cpp_cmd():
    "Build command list for preprocessing the header file."
    cmd = dev.build.COMPILE['.c'][:]
    cmd.append('-nostdinc')
    cmd.append('-I%s' % ('dev/pycparser/utils/fake_libc_include', ))
    cmd += ['-E', os.path.join('lib', 'include', 'sddekit.h')]
    return cmd

PPFNAME = os.path.join(dev.build.BUILD_DIR, 'sddekit_pp.h')

def preprocess_header():
    cmd = build_cpp_cmd()
    LOG.info(cmd)
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    proc.wait()
    header = proc.stdout.read().decode('utf-8').replace('\r', '')
    with open(PPFNAME, 'w') as fd:
        fd.write(header)

def header_ast():
    if not os.path.exists(PPFNAME):
        preprocess_header()
    with open(PPFNAME, 'r') as fd:
        src = fd.read()
    cp = pycparser.CParser()
    ast = cp.parse(src, PPFNAME)
    return ast
