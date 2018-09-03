# copyright 2016 Apache 2 libtvb authors

"""
This package supports API introspection.

"""

import os.path
import warnings
import logging

LOG = logging.getLogger(__name__)

if os.path.exists('dev/pycparser/pycparser'):
    import sys
    sys.path.insert(0, 'dev/pycparser')
    import pycparser
    LOG.debug("pycparser found at %r", pycparser.__path__)
else:
    LOG.warn('pycparser sources not checked out.')
    LOG.warn('did you forget to git submodule init && git submodule update?')