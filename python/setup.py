# copyright 2016 Apache 2 sddekit authors

import os
import glob
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

here = os.path.dirname(os.path.abspath(__file__))
up = os.path.dirname(here)
sources = glob.glob(os.path.join(here, '*.pyx')) + glob.glob(os.path.join(up, 'src/*.c'))
incpath = os.path.join(up, 'include')

setup(
    name="sddekit",
    ext_modules=cythonize([
            Extension("sddekit", sources=sources, include_dirs=[incpath])
        ]),
)
