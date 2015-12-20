from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

setup(
  name = 'cb',
  ext_modules=cythonize([
    Extension("pylib", ["pylib.pyx", "lib.c"]),
    ]),
)
