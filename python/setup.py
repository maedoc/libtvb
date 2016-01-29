# copyright 2016 Apache 2 sddekit authors

import os
import glob
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy as np

here = os.path.dirname(os.path.abspath(__file__))
up = os.path.dirname(here)

sources = []
for d, p in ((here, '*.pyx'), (up, 'src/*.c')):
    sources += glob.glob(os.path.join(d, p))

ext = Extension('hist',
        sources=sources,
        include_dirs=[
            os.path.join(up, 'src'),
            np.get_include()
            ]
        )

setup(
    name="sddekit",
    ext_modules=cythonize([ext]),
)
