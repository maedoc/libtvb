# copyright 2016 Apache 2 sddekit authors

import os
import glob
from distutils.core import setup, Extension
import numpy as np

here = os.path.dirname(os.path.abspath(__file__))
sources = glob.glob('src/*.c')

mod = Extension(
        'sddekit', 
        sources=['sddekit.c'] + sources,
        include_dirs=['src', np.get_include()])

setup(name='SDDEKit',
      version=0.0,
      description='n/a',
      ext_modules=[mod])
