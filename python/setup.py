# copyright 2016 Apache 2 sddekit authors

import os
import glob
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy as np

here = os.path.dirname(os.path.abspath(__file__))
up = os.path.dirname(here)

exts = [
        Extension('sddekit',
            sources=[os.path.join(here, 'sddekit.pyx')] + \
                    glob.glob(os.path.join(up, 'src/*.c')),
            include_dirs=[
                os.path.join(up, 'src'),
                np.get_include()
                ]
            )
        ]

setup(
        name="sddekit",
        ext_modules=cythonize(exts),
        )

# vim: sw=4 sts=4 et
