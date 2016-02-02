'''Wrapper for sddekit.h

Generated with:
ctypesgen/ctypesgen.py -L /home/mw/dev/sddekit -lSDDEKit /home/mw/dev/sddekit/src/sddekit.h -o /home/mw/dev/sddekit/python/_sddekit.py

Do not modify this file.
'''

__docformat__ =  'restructuredtext'

# Begin preamble

import ctypes, os, sys
from ctypes import *

_int_types = (c_int16, c_int32)
if hasattr(ctypes, 'c_int64'):
    # Some builds of ctypes apparently do not have c_int64
    # defined; it's a pretty good bet that these builds do not
    # have 64-bit pointers.
    _int_types += (c_int64,)
for t in _int_types:
    if sizeof(t) == sizeof(c_size_t):
        c_ptrdiff_t = t
del t
del _int_types

class c_void(Structure):
    # c_void_p is a buggy return type, converting to int, so
    # POINTER(None) == c_void_p is actually written as
    # POINTER(c_void), so it can be treated as a real pointer.
    _fields_ = [('dummy', c_int)]

def POINTER(obj):
    p = ctypes.POINTER(obj)

    # Convert None to a real NULL pointer to work around bugs
    # in how ctypes handles None on 64-bit platforms
    if not isinstance(p.from_param, classmethod):
        def from_param(cls, x):
            if x is None:
                return cls()
            else:
                return x
        p.from_param = classmethod(from_param)

    return p

class UserString:
    def __init__(self, seq):
        if isinstance(seq, basestring):
            self.data = seq
        elif isinstance(seq, UserString):
            self.data = seq.data[:]
        else:
            self.data = str(seq)
    def __str__(self): return str(self.data)
    def __repr__(self): return repr(self.data)
    def __int__(self): return int(self.data)
    def __long__(self): return long(self.data)
    def __float__(self): return float(self.data)
    def __complex__(self): return complex(self.data)
    def __hash__(self): return hash(self.data)

    def __cmp__(self, string):
        if isinstance(string, UserString):
            return cmp(self.data, string.data)
        else:
            return cmp(self.data, string)
    def __contains__(self, char):
        return char in self.data

    def __len__(self): return len(self.data)
    def __getitem__(self, index): return self.__class__(self.data[index])
    def __getslice__(self, start, end):
        start = max(start, 0); end = max(end, 0)
        return self.__class__(self.data[start:end])

    def __add__(self, other):
        if isinstance(other, UserString):
            return self.__class__(self.data + other.data)
        elif isinstance(other, basestring):
            return self.__class__(self.data + other)
        else:
            return self.__class__(self.data + str(other))
    def __radd__(self, other):
        if isinstance(other, basestring):
            return self.__class__(other + self.data)
        else:
            return self.__class__(str(other) + self.data)
    def __mul__(self, n):
        return self.__class__(self.data*n)
    __rmul__ = __mul__
    def __mod__(self, args):
        return self.__class__(self.data % args)

    # the following methods are defined in alphabetical order:
    def capitalize(self): return self.__class__(self.data.capitalize())
    def center(self, width, *args):
        return self.__class__(self.data.center(width, *args))
    def count(self, sub, start=0, end=sys.maxint):
        return self.data.count(sub, start, end)
    def decode(self, encoding=None, errors=None): # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.decode(encoding, errors))
            else:
                return self.__class__(self.data.decode(encoding))
        else:
            return self.__class__(self.data.decode())
    def encode(self, encoding=None, errors=None): # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.encode(encoding, errors))
            else:
                return self.__class__(self.data.encode(encoding))
        else:
            return self.__class__(self.data.encode())
    def endswith(self, suffix, start=0, end=sys.maxint):
        return self.data.endswith(suffix, start, end)
    def expandtabs(self, tabsize=8):
        return self.__class__(self.data.expandtabs(tabsize))
    def find(self, sub, start=0, end=sys.maxint):
        return self.data.find(sub, start, end)
    def index(self, sub, start=0, end=sys.maxint):
        return self.data.index(sub, start, end)
    def isalpha(self): return self.data.isalpha()
    def isalnum(self): return self.data.isalnum()
    def isdecimal(self): return self.data.isdecimal()
    def isdigit(self): return self.data.isdigit()
    def islower(self): return self.data.islower()
    def isnumeric(self): return self.data.isnumeric()
    def isspace(self): return self.data.isspace()
    def istitle(self): return self.data.istitle()
    def isupper(self): return self.data.isupper()
    def join(self, seq): return self.data.join(seq)
    def ljust(self, width, *args):
        return self.__class__(self.data.ljust(width, *args))
    def lower(self): return self.__class__(self.data.lower())
    def lstrip(self, chars=None): return self.__class__(self.data.lstrip(chars))
    def partition(self, sep):
        return self.data.partition(sep)
    def replace(self, old, new, maxsplit=-1):
        return self.__class__(self.data.replace(old, new, maxsplit))
    def rfind(self, sub, start=0, end=sys.maxint):
        return self.data.rfind(sub, start, end)
    def rindex(self, sub, start=0, end=sys.maxint):
        return self.data.rindex(sub, start, end)
    def rjust(self, width, *args):
        return self.__class__(self.data.rjust(width, *args))
    def rpartition(self, sep):
        return self.data.rpartition(sep)
    def rstrip(self, chars=None): return self.__class__(self.data.rstrip(chars))
    def split(self, sep=None, maxsplit=-1):
        return self.data.split(sep, maxsplit)
    def rsplit(self, sep=None, maxsplit=-1):
        return self.data.rsplit(sep, maxsplit)
    def splitlines(self, keepends=0): return self.data.splitlines(keepends)
    def startswith(self, prefix, start=0, end=sys.maxint):
        return self.data.startswith(prefix, start, end)
    def strip(self, chars=None): return self.__class__(self.data.strip(chars))
    def swapcase(self): return self.__class__(self.data.swapcase())
    def title(self): return self.__class__(self.data.title())
    def translate(self, *args):
        return self.__class__(self.data.translate(*args))
    def upper(self): return self.__class__(self.data.upper())
    def zfill(self, width): return self.__class__(self.data.zfill(width))

class MutableString(UserString):
    """mutable string objects

    Python strings are immutable objects.  This has the advantage, that
    strings may be used as dictionary keys.  If this property isn't needed
    and you insist on changing string values in place instead, you may cheat
    and use MutableString.

    But the purpose of this class is an educational one: to prevent
    people from inventing their own mutable string class derived
    from UserString and than forget thereby to remove (override) the
    __hash__ method inherited from UserString.  This would lead to
    errors that would be very hard to track down.

    A faster and better solution is to rewrite your program using lists."""
    def __init__(self, string=""):
        self.data = string
    def __hash__(self):
        raise TypeError("unhashable type (it is mutable)")
    def __setitem__(self, index, sub):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data): raise IndexError
        self.data = self.data[:index] + sub + self.data[index+1:]
    def __delitem__(self, index):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data): raise IndexError
        self.data = self.data[:index] + self.data[index+1:]
    def __setslice__(self, start, end, sub):
        start = max(start, 0); end = max(end, 0)
        if isinstance(sub, UserString):
            self.data = self.data[:start]+sub.data+self.data[end:]
        elif isinstance(sub, basestring):
            self.data = self.data[:start]+sub+self.data[end:]
        else:
            self.data =  self.data[:start]+str(sub)+self.data[end:]
    def __delslice__(self, start, end):
        start = max(start, 0); end = max(end, 0)
        self.data = self.data[:start] + self.data[end:]
    def immutable(self):
        return UserString(self.data)
    def __iadd__(self, other):
        if isinstance(other, UserString):
            self.data += other.data
        elif isinstance(other, basestring):
            self.data += other
        else:
            self.data += str(other)
        return self
    def __imul__(self, n):
        self.data *= n
        return self

class String(MutableString, Union):

    _fields_ = [('raw', POINTER(c_char)),
                ('data', c_char_p)]

    def __init__(self, obj=""):
        if isinstance(obj, (str, unicode, UserString)):
            self.data = str(obj)
        else:
            self.raw = obj

    def __len__(self):
        return self.data and len(self.data) or 0

    def from_param(cls, obj):
        # Convert None or 0
        if obj is None or obj == 0:
            return cls(POINTER(c_char)())

        # Convert from String
        elif isinstance(obj, String):
            return obj

        # Convert from str
        elif isinstance(obj, str):
            return cls(obj)

        # Convert from c_char_p
        elif isinstance(obj, c_char_p):
            return obj

        # Convert from POINTER(c_char)
        elif isinstance(obj, POINTER(c_char)):
            return obj

        # Convert from raw pointer
        elif isinstance(obj, int):
            return cls(cast(obj, POINTER(c_char)))

        # Convert from object
        else:
            return String.from_param(obj._as_parameter_)
    from_param = classmethod(from_param)

def ReturnString(obj, func=None, arguments=None):
    return String.from_param(obj)

# As of ctypes 1.0, ctypes does not support custom error-checking
# functions on callbacks, nor does it support custom datatypes on
# callbacks, so we must ensure that all callbacks return
# primitive datatypes.
#
# Non-primitive return values wrapped with UNCHECKED won't be
# typechecked, and will be converted to c_void_p.
def UNCHECKED(type):
    if (hasattr(type, "_type_") and isinstance(type._type_, str)
        and type._type_ != "P"):
        return type
    else:
        return c_void_p

# ctypes doesn't have direct support for variadic functions, so we have to write
# our own wrapper class
class _variadic_function(object):
    def __init__(self,func,restype,argtypes):
        self.func=func
        self.func.restype=restype
        self.argtypes=argtypes
    def _as_parameter_(self):
        # So we can pass this variadic function as a function pointer
        return self.func
    def __call__(self,*args):
        fixed_args=[]
        i=0
        for argtype in self.argtypes:
            # Typecheck what we can
            fixed_args.append(argtype.from_param(args[i]))
            i+=1
        return self.func(*fixed_args+list(args[i:]))

# End preamble

_libs = {}
_libdirs = ['/home/mw/dev/sddekit']

# Begin loader

# ----------------------------------------------------------------------------
# Copyright (c) 2008 David James
# Copyright (c) 2006-2008 Alex Holkner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of pyglet nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

import os.path, re, sys, glob
import platform
import ctypes
import ctypes.util

def _environ_path(name):
    if name in os.environ:
        return os.environ[name].split(":")
    else:
        return []

class LibraryLoader(object):
    def __init__(self):
        self.other_dirs=[]

    def load_library(self,libname):
        """Given the name of a library, load it."""
        paths = self.getpaths(libname)

        for path in paths:
            if os.path.exists(path):
                return self.load(path)

        raise ImportError("%s not found." % libname)

    def load(self,path):
        """Given a path to a library, load it."""
        try:
            # Darwin requires dlopen to be called with mode RTLD_GLOBAL instead
            # of the default RTLD_LOCAL.  Without this, you end up with
            # libraries not being loadable, resulting in "Symbol not found"
            # errors
            if sys.platform == 'darwin':
                return ctypes.CDLL(path, ctypes.RTLD_GLOBAL)
            else:
                return ctypes.cdll.LoadLibrary(path)
        except OSError,e:
            raise ImportError(e)

    def getpaths(self,libname):
        """Return a list of paths where the library might be found."""
        if os.path.isabs(libname):
            yield libname
        else:
            # FIXME / TODO return '.' and os.path.dirname(__file__)
            for path in self.getplatformpaths(libname):
                yield path

            path = ctypes.util.find_library(libname)
            if path: yield path

    def getplatformpaths(self, libname):
        return []

# Darwin (Mac OS X)

class DarwinLibraryLoader(LibraryLoader):
    name_formats = ["lib%s.dylib", "lib%s.so", "lib%s.bundle", "%s.dylib",
                "%s.so", "%s.bundle", "%s"]

    def getplatformpaths(self,libname):
        if os.path.pathsep in libname:
            names = [libname]
        else:
            names = [format % libname for format in self.name_formats]

        for dir in self.getdirs(libname):
            for name in names:
                yield os.path.join(dir,name)

    def getdirs(self,libname):
        '''Implements the dylib search as specified in Apple documentation:

        http://developer.apple.com/documentation/DeveloperTools/Conceptual/
            DynamicLibraries/Articles/DynamicLibraryUsageGuidelines.html

        Before commencing the standard search, the method first checks
        the bundle's ``Frameworks`` directory if the application is running
        within a bundle (OS X .app).
        '''

        dyld_fallback_library_path = _environ_path("DYLD_FALLBACK_LIBRARY_PATH")
        if not dyld_fallback_library_path:
            dyld_fallback_library_path = [os.path.expanduser('~/lib'),
                                          '/usr/local/lib', '/usr/lib']

        dirs = []

        if '/' in libname:
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
        else:
            dirs.extend(_environ_path("LD_LIBRARY_PATH"))
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))

        dirs.extend(self.other_dirs)
        dirs.append(".")
        dirs.append(os.path.dirname(__file__))

        if hasattr(sys, 'frozen') and sys.frozen == 'macosx_app':
            dirs.append(os.path.join(
                os.environ['RESOURCEPATH'],
                '..',
                'Frameworks'))

        dirs.extend(dyld_fallback_library_path)

        return dirs

# Posix

class PosixLibraryLoader(LibraryLoader):
    _ld_so_cache = None

    def _create_ld_so_cache(self):
        # Recreate search path followed by ld.so.  This is going to be
        # slow to build, and incorrect (ld.so uses ld.so.cache, which may
        # not be up-to-date).  Used only as fallback for distros without
        # /sbin/ldconfig.
        #
        # We assume the DT_RPATH and DT_RUNPATH binary sections are omitted.

        directories = []
        for name in ("LD_LIBRARY_PATH",
                     "SHLIB_PATH", # HPUX
                     "LIBPATH", # OS/2, AIX
                     "LIBRARY_PATH", # BE/OS
                    ):
            if name in os.environ:
                directories.extend(os.environ[name].split(os.pathsep))
        directories.extend(self.other_dirs)
        directories.append(".")
        directories.append(os.path.dirname(__file__))

        try: directories.extend([dir.strip() for dir in open('/etc/ld.so.conf')])
        except IOError: pass

        unix_lib_dirs_list = ['/lib', '/usr/lib', '/lib64', '/usr/lib64']
        if sys.platform.startswith('linux'):
            # Try and support multiarch work in Ubuntu
            # https://wiki.ubuntu.com/MultiarchSpec
            bitage = platform.architecture()[0]
            if bitage.startswith('32'):
                # Assume Intel/AMD x86 compat
                unix_lib_dirs_list += ['/lib/i386-linux-gnu', '/usr/lib/i386-linux-gnu']
            elif bitage.startswith('64'):
                # Assume Intel/AMD x86 compat
                unix_lib_dirs_list += ['/lib/x86_64-linux-gnu', '/usr/lib/x86_64-linux-gnu']
            else:
                # guess...
                unix_lib_dirs_list += glob.glob('/lib/*linux-gnu')
        directories.extend(unix_lib_dirs_list)

        cache = {}
        lib_re = re.compile(r'lib(.*)\.s[ol]')
        ext_re = re.compile(r'\.s[ol]$')
        for dir in directories:
            try:
                for path in glob.glob("%s/*.s[ol]*" % dir):
                    file = os.path.basename(path)

                    # Index by filename
                    if file not in cache:
                        cache[file] = path

                    # Index by library name
                    match = lib_re.match(file)
                    if match:
                        library = match.group(1)
                        if library not in cache:
                            cache[library] = path
            except OSError:
                pass

        self._ld_so_cache = cache

    def getplatformpaths(self, libname):
        if self._ld_so_cache is None:
            self._create_ld_so_cache()

        result = self._ld_so_cache.get(libname)
        if result: yield result

        path = ctypes.util.find_library(libname)
        if path: yield os.path.join("/lib",path)

# Windows

class _WindowsLibrary(object):
    def __init__(self, path):
        self.cdll = ctypes.cdll.LoadLibrary(path)
        self.windll = ctypes.windll.LoadLibrary(path)

    def __getattr__(self, name):
        try: return getattr(self.cdll,name)
        except AttributeError:
            try: return getattr(self.windll,name)
            except AttributeError:
                raise

class WindowsLibraryLoader(LibraryLoader):
    name_formats = ["%s.dll", "lib%s.dll", "%slib.dll"]

    def load_library(self, libname):
        try:
            result = LibraryLoader.load_library(self, libname)
        except ImportError:
            result = None
            if os.path.sep not in libname:
                for name in self.name_formats:
                    try:
                        result = getattr(ctypes.cdll, name % libname)
                        if result:
                            break
                    except WindowsError:
                        result = None
            if result is None:
                try:
                    result = getattr(ctypes.cdll, libname)
                except WindowsError:
                    result = None
            if result is None:
                raise ImportError("%s not found." % libname)
        return result

    def load(self, path):
        return _WindowsLibrary(path)

    def getplatformpaths(self, libname):
        if os.path.sep not in libname:
            for name in self.name_formats:
                dll_in_current_dir = os.path.abspath(name % libname)
                if os.path.exists(dll_in_current_dir):
                    yield dll_in_current_dir
                path = ctypes.util.find_library(name % libname)
                if path:
                    yield path

# Platform switching

# If your value of sys.platform does not appear in this dict, please contact
# the Ctypesgen maintainers.

loaderclass = {
    "darwin":   DarwinLibraryLoader,
    "cygwin":   WindowsLibraryLoader,
    "win32":    WindowsLibraryLoader
}

loader = loaderclass.get(sys.platform, PosixLibraryLoader)()

def add_library_search_dirs(other_dirs):
    loader.other_dirs = other_dirs

load_library = loader.load_library

del loaderclass

# End loader

add_library_search_dirs(['/home/mw/dev/sddekit'])

# Begin libraries

_libs["SDDEKit"] = load_library("SDDEKit")

# 1 libraries
# End libraries

# No modules

__off_t = c_long # /usr/include/bits/types.h: 131

__off64_t = c_long # /usr/include/bits/types.h: 132

# /usr/include/libio.h: 245
class struct__IO_FILE(Structure):
    pass

FILE = struct__IO_FILE # /usr/include/stdio.h: 48

_IO_lock_t = None # /usr/include/libio.h: 154

# /usr/include/libio.h: 160
class struct__IO_marker(Structure):
    pass

struct__IO_marker.__slots__ = [
    '_next',
    '_sbuf',
    '_pos',
]
struct__IO_marker._fields_ = [
    ('_next', POINTER(struct__IO_marker)),
    ('_sbuf', POINTER(struct__IO_FILE)),
    ('_pos', c_int),
]

struct__IO_FILE.__slots__ = [
    '_flags',
    '_IO_read_ptr',
    '_IO_read_end',
    '_IO_read_base',
    '_IO_write_base',
    '_IO_write_ptr',
    '_IO_write_end',
    '_IO_buf_base',
    '_IO_buf_end',
    '_IO_save_base',
    '_IO_backup_base',
    '_IO_save_end',
    '_markers',
    '_chain',
    '_fileno',
    '_flags2',
    '_old_offset',
    '_cur_column',
    '_vtable_offset',
    '_shortbuf',
    '_lock',
    '_offset',
    '__pad1',
    '__pad2',
    '__pad3',
    '__pad4',
    '__pad5',
    '_mode',
    '_unused2',
]
struct__IO_FILE._fields_ = [
    ('_flags', c_int),
    ('_IO_read_ptr', String),
    ('_IO_read_end', String),
    ('_IO_read_base', String),
    ('_IO_write_base', String),
    ('_IO_write_ptr', String),
    ('_IO_write_end', String),
    ('_IO_buf_base', String),
    ('_IO_buf_end', String),
    ('_IO_save_base', String),
    ('_IO_backup_base', String),
    ('_IO_save_end', String),
    ('_markers', POINTER(struct__IO_marker)),
    ('_chain', POINTER(struct__IO_FILE)),
    ('_fileno', c_int),
    ('_flags2', c_int),
    ('_old_offset', __off_t),
    ('_cur_column', c_ushort),
    ('_vtable_offset', c_char),
    ('_shortbuf', c_char * 1),
    ('_lock', POINTER(_IO_lock_t)),
    ('_offset', __off64_t),
    ('__pad1', POINTER(None)),
    ('__pad2', POINTER(None)),
    ('__pad3', POINTER(None)),
    ('__pad4', POINTER(None)),
    ('__pad5', c_size_t),
    ('_mode', c_int),
    ('_unused2', c_char * (((15 * sizeof(c_int)) - (4 * sizeof(POINTER(None)))) - sizeof(c_size_t))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 55
if hasattr(_libs['SDDEKit'], 'sd_ver_major'):
    sd_ver_major = _libs['SDDEKit'].sd_ver_major
    sd_ver_major.argtypes = []
    sd_ver_major.restype = c_uint32

# /home/mw/dev/sddekit/src/sddekit.h: 56
if hasattr(_libs['SDDEKit'], 'sd_ver_minor'):
    sd_ver_minor = _libs['SDDEKit'].sd_ver_minor
    sd_ver_minor.argtypes = []
    sd_ver_minor.restype = c_uint32

enum_sd_stat = c_int # /home/mw/dev/sddekit/src/sddekit.h: 70

SD_OK = 0 # /home/mw/dev/sddekit/src/sddekit.h: 70

SD_ERR = (SD_OK + 1) # /home/mw/dev/sddekit/src/sddekit.h: 70

SD_CONT = (SD_ERR + 1) # /home/mw/dev/sddekit/src/sddekit.h: 70

SD_STOP = (SD_CONT + 1) # /home/mw/dev/sddekit/src/sddekit.h: 70

sd_stat = enum_sd_stat # /home/mw/dev/sddekit/src/sddekit.h: 70

# /home/mw/dev/sddekit/src/sddekit.h: 83
if hasattr(_libs['SDDEKit'], 'sd_util_read_square_matrix'):
    sd_util_read_square_matrix = _libs['SDDEKit'].sd_util_read_square_matrix
    sd_util_read_square_matrix.argtypes = [String, POINTER(c_uint32), POINTER(POINTER(c_double))]
    sd_util_read_square_matrix.restype = sd_stat

# /home/mw/dev/sddekit/src/sddekit.h: 95
if hasattr(_libs['SDDEKit'], 'sd_util_uniqi'):
    sd_util_uniqi = _libs['SDDEKit'].sd_util_uniqi
    sd_util_uniqi.argtypes = [c_uint32, POINTER(c_uint32), POINTER(c_uint32), POINTER(POINTER(c_uint32))]
    sd_util_uniqi.restype = sd_stat

# /home/mw/dev/sddekit/src/sddekit.h: 112
class struct_sd_rng(Structure):
    pass

sd_rng = struct_sd_rng # /home/mw/dev/sddekit/src/sddekit.h: 105

struct_sd_rng.__slots__ = [
    'ptr',
    'seed',
    'norm',
    'fill_norm',
    'nbytes',
    'free',
]
struct_sd_rng._fields_ = [
    ('ptr', POINTER(None)),
    ('seed', CFUNCTYPE(UNCHECKED(None), POINTER(sd_rng), c_uint32)),
    ('norm', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_rng))),
    ('fill_norm', CFUNCTYPE(UNCHECKED(None), POINTER(sd_rng), c_uint32, POINTER(c_double))),
    ('nbytes', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_rng))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_rng))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 137
if hasattr(_libs['SDDEKit'], 'sd_rng_seed'):
    sd_rng_seed = _libs['SDDEKit'].sd_rng_seed
    sd_rng_seed.argtypes = [POINTER(sd_rng), c_uint32]
    sd_rng_seed.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 138
if hasattr(_libs['SDDEKit'], 'sd_rng_norm'):
    sd_rng_norm = _libs['SDDEKit'].sd_rng_norm
    sd_rng_norm.argtypes = [POINTER(sd_rng)]
    sd_rng_norm.restype = c_double

# /home/mw/dev/sddekit/src/sddekit.h: 139
if hasattr(_libs['SDDEKit'], 'sd_rng_fill_norm'):
    sd_rng_fill_norm = _libs['SDDEKit'].sd_rng_fill_norm
    sd_rng_fill_norm.argtypes = [POINTER(sd_rng), c_uint32, POINTER(c_double)]
    sd_rng_fill_norm.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 140
if hasattr(_libs['SDDEKit'], 'sd_rng_nbytes'):
    sd_rng_nbytes = _libs['SDDEKit'].sd_rng_nbytes
    sd_rng_nbytes.argtypes = [POINTER(sd_rng)]
    sd_rng_nbytes.restype = c_uint32

# /home/mw/dev/sddekit/src/sddekit.h: 141
if hasattr(_libs['SDDEKit'], 'sd_rng_free'):
    sd_rng_free = _libs['SDDEKit'].sd_rng_free
    sd_rng_free.argtypes = [POINTER(sd_rng)]
    sd_rng_free.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 146
if hasattr(_libs['SDDEKit'], 'sd_rng_new_default'):
    sd_rng_new_default = _libs['SDDEKit'].sd_rng_new_default
    sd_rng_new_default.argtypes = []
    sd_rng_new_default.restype = POINTER(sd_rng)

# /home/mw/dev/sddekit/src/sddekit.h: 159
class struct_sd_hfill(Structure):
    pass

sd_hfill = struct_sd_hfill # /home/mw/dev/sddekit/src/sddekit.h: 154

struct_sd_hfill.__slots__ = [
    'ptr',
    'apply',
    'free',
]
struct_sd_hfill._fields_ = [
    ('ptr', POINTER(None)),
    ('apply', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_hfill), c_uint32, POINTER(c_double), POINTER(c_uint32), POINTER(c_double))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_hfill))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 180
if hasattr(_libs['SDDEKit'], 'sd_hfill_apply'):
    sd_hfill_apply = _libs['SDDEKit'].sd_hfill_apply
    sd_hfill_apply.argtypes = [POINTER(sd_hfill), c_uint32, POINTER(c_double), POINTER(c_uint32), POINTER(c_double)]
    sd_hfill_apply.restype = sd_stat

# /home/mw/dev/sddekit/src/sddekit.h: 182
if hasattr(_libs['SDDEKit'], 'sd_hfill_free'):
    sd_hfill_free = _libs['SDDEKit'].sd_hfill_free
    sd_hfill_free.argtypes = [POINTER(sd_hfill)]
    sd_hfill_free.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 187
if hasattr(_libs['SDDEKit'], 'sd_hfill_new_val'):
    sd_hfill_new_val = _libs['SDDEKit'].sd_hfill_new_val
    sd_hfill_new_val.argtypes = [c_double]
    sd_hfill_new_val.restype = POINTER(sd_hfill)

# /home/mw/dev/sddekit/src/sddekit.h: 197
class struct_sd_hist(Structure):
    pass

sd_hist = struct_sd_hist # /home/mw/dev/sddekit/src/sddekit.h: 195

struct_sd_hist.__slots__ = [
    'ptr',
    'get_maxvi',
    'get_vi2i',
    'get_nu',
    'free',
    'fill',
    'get',
    'set',
    'nbytes',
    'get_buf_lin',
    'get_nd',
    'get_t',
    'get_dt',
    'get_lim',
    'get_len',
    'get_pos',
    'get_uvi',
    'get_maxd',
    'get_vi',
    'get_vd',
    'buf_is_null',
]
struct_sd_hist._fields_ = [
    ('ptr', POINTER(None)),
    ('get_maxvi', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist))),
    ('get_vi2i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_nu', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_hist))),
    ('fill', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_hist), POINTER(sd_hfill))),
    ('get', CFUNCTYPE(UNCHECKED(None), POINTER(sd_hist), c_double, POINTER(c_double))),
    ('set', CFUNCTYPE(UNCHECKED(None), POINTER(sd_hist), c_double, POINTER(c_double))),
    ('nbytes', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist))),
    ('get_buf_lin', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_hist), c_uint32)),
    ('get_nd', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist))),
    ('get_t', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_hist))),
    ('get_dt', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_hist))),
    ('get_lim', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_len', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_pos', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_uvi', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_maxd', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_hist), c_uint32)),
    ('get_vi', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_hist), c_uint32)),
    ('get_vd', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_hist), c_uint32)),
    ('buf_is_null', CFUNCTYPE(UNCHECKED(c_bool), POINTER(sd_hist))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 374
if hasattr(_libs['SDDEKit'], 'sd_hist_new_default'):
    sd_hist_new_default = _libs['SDDEKit'].sd_hist_new_default
    sd_hist_new_default.argtypes = [c_uint32, POINTER(c_uint32), POINTER(c_double), c_double, c_double]
    sd_hist_new_default.restype = POINTER(sd_hist)

sd_malloc_t = CFUNCTYPE(UNCHECKED(POINTER(None)), c_size_t) # /home/mw/dev/sddekit/src/sddekit.h: 382

sd_realloc_t = CFUNCTYPE(UNCHECKED(POINTER(None)), POINTER(None), c_size_t) # /home/mw/dev/sddekit/src/sddekit.h: 383

sd_free_t = CFUNCTYPE(UNCHECKED(None), POINTER(None)) # /home/mw/dev/sddekit/src/sddekit.h: 384

# /home/mw/dev/sddekit/src/sddekit.h: 391
if hasattr(_libs['SDDEKit'], 'sd_malloc_set_allocators'):
    sd_malloc_set_allocators = _libs['SDDEKit'].sd_malloc_set_allocators
    sd_malloc_set_allocators.argtypes = [sd_malloc_t, sd_realloc_t, sd_free_t]
    sd_malloc_set_allocators.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 397
if hasattr(_libs['SDDEKit'], 'sd_malloc_set_stdlib_allocators'):
    sd_malloc_set_stdlib_allocators = _libs['SDDEKit'].sd_malloc_set_stdlib_allocators
    sd_malloc_set_stdlib_allocators.argtypes = []
    sd_malloc_set_stdlib_allocators.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 402
if hasattr(_libs['SDDEKit'], 'sd_malloc'):
    sd_malloc = _libs['SDDEKit'].sd_malloc
    sd_malloc.argtypes = [c_size_t]
    sd_malloc.restype = POINTER(None)

# /home/mw/dev/sddekit/src/sddekit.h: 408
if hasattr(_libs['SDDEKit'], 'sd_realloc'):
    sd_realloc = _libs['SDDEKit'].sd_realloc
    sd_realloc.argtypes = [POINTER(None), c_size_t]
    sd_realloc.restype = POINTER(None)

# /home/mw/dev/sddekit/src/sddekit.h: 415
if hasattr(_libs['SDDEKit'], 'sd_free'):
    sd_free = _libs['SDDEKit'].sd_free
    sd_free.argtypes = [POINTER(None)]
    sd_free.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 458
class struct_sd_sys_in(Structure):
    pass

struct_sd_sys_in.__slots__ = [
    'nx',
    'nc',
    'id',
    't',
    'x',
    'i',
    'hist',
    'rng',
]
struct_sd_sys_in._fields_ = [
    ('nx', c_uint32),
    ('nc', c_uint32),
    ('id', c_uint32),
    ('t', c_double),
    ('x', POINTER(c_double)),
    ('i', POINTER(c_double)),
    ('hist', POINTER(sd_hist)),
    ('rng', POINTER(sd_rng)),
]

sd_sys_in = struct_sd_sys_in # /home/mw/dev/sddekit/src/sddekit.h: 458

# /home/mw/dev/sddekit/src/sddekit.h: 462
class struct_sd_sys_out(Structure):
    pass

struct_sd_sys_out.__slots__ = [
    'f',
    'g',
    'o',
]
struct_sd_sys_out._fields_ = [
    ('f', POINTER(c_double)),
    ('g', POINTER(c_double)),
    ('o', POINTER(c_double)),
]

sd_sys_out = struct_sd_sys_out # /home/mw/dev/sddekit/src/sddekit.h: 462

# /home/mw/dev/sddekit/src/sddekit.h: 470
class struct_sd_sys(Structure):
    pass

sd_sys = struct_sd_sys # /home/mw/dev/sddekit/src/sddekit.h: 465

struct_sd_sys.__slots__ = [
    'ndim',
    'ndc',
    'nobs',
    'nrpar',
    'nipar',
    'apply',
    'free',
    'ptr',
]
struct_sd_sys._fields_ = [
    ('ndim', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sys))),
    ('ndc', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sys))),
    ('nobs', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sys))),
    ('nrpar', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sys))),
    ('nipar', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sys))),
    ('apply', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_sys), POINTER(sd_sys_in), POINTER(sd_sys_out))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sys))),
    ('ptr', POINTER(None)),
]

# /home/mw/dev/sddekit/src/sddekit.h: 516
if hasattr(_libs['SDDEKit'], 'sd_sys_new_cb'):
    sd_sys_new_cb = _libs['SDDEKit'].sd_sys_new_cb
    sd_sys_new_cb.argtypes = [c_uint32, c_uint32, c_uint32, c_uint32, c_uint32, POINTER(None), CFUNCTYPE(UNCHECKED(sd_stat), POINTER(None), POINTER(sd_sys_in), POINTER(sd_sys_out))]
    sd_sys_new_cb.restype = POINTER(sd_sys)

# /home/mw/dev/sddekit/src/sddekit.h: 533
class struct_sd_sys_exc(Structure):
    pass

sd_sys_exc = struct_sd_sys_exc # /home/mw/dev/sddekit/src/sddekit.h: 528

struct_sd_sys_exc.__slots__ = [
    'ptr',
    'sys',
    'get_a',
    'set_a',
    'get_tau',
    'set_tau',
    'get_D',
    'set_D',
    'get_k',
    'set_k',
]
struct_sd_sys_exc._fields_ = [
    ('ptr', POINTER(None)),
    ('sys', CFUNCTYPE(UNCHECKED(POINTER(sd_sys)), POINTER(sd_sys_exc))),
    ('get_a', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_sys_exc))),
    ('set_a', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sys_exc), c_double)),
    ('get_tau', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_sys_exc))),
    ('set_tau', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sys_exc), c_double)),
    ('get_D', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_sys_exc))),
    ('set_D', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sys_exc), c_double)),
    ('get_k', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_sys_exc))),
    ('set_k', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sys_exc), c_double)),
]

# /home/mw/dev/sddekit/src/sddekit.h: 607
if hasattr(_libs['SDDEKit'], 'sd_sys_exc_new'):
    sd_sys_exc_new = _libs['SDDEKit'].sd_sys_exc_new
    sd_sys_exc_new.argtypes = []
    sd_sys_exc_new.restype = POINTER(sd_sys_exc)

# /home/mw/dev/sddekit/src/sddekit.h: 649
class struct_sd_net(Structure):
    pass

sd_net = struct_sd_net # /home/mw/dev/sddekit/src/sddekit.h: 644

struct_sd_net.__slots__ = [
    'ptr',
    'sys',
    'free',
    'get_n',
    'get_m',
    'get_nnz',
    'get_or',
    'get_or_i',
    'get_ic',
    'get_ic_i',
    'get_w',
    'get_w_i',
    'get_d',
    'get_d_i',
    'get_ns',
    'get_ne',
    'cn_is_null',
    'get_Ms_i',
    'get_Ma_i',
    'get_Me_i',
    'get_M_i',
    'get_models_i',
    'get__init1',
]
struct_sd_net._fields_ = [
    ('ptr', POINTER(None)),
    ('sys', CFUNCTYPE(UNCHECKED(POINTER(sd_sys)), POINTER(sd_net))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_net))),
    ('get_n', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net))),
    ('get_m', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net))),
    ('get_nnz', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net))),
    ('get_or', CFUNCTYPE(UNCHECKED(POINTER(c_uint32)), POINTER(sd_net))),
    ('get_or_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_ic', CFUNCTYPE(UNCHECKED(POINTER(c_uint32)), POINTER(sd_net))),
    ('get_ic_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_w', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_net))),
    ('get_w_i', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_net), c_uint32)),
    ('get_d', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_net))),
    ('get_d_i', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_net), c_uint32)),
    ('get_ns', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net))),
    ('get_ne', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net))),
    ('cn_is_null', CFUNCTYPE(UNCHECKED(c_bool), POINTER(sd_net))),
    ('get_Ms_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_Ma_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_Me_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_M_i', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_net), c_uint32)),
    ('get_models_i', CFUNCTYPE(UNCHECKED(POINTER(sd_sys)), POINTER(sd_net), c_uint32)),
    ('get__init1', CFUNCTYPE(UNCHECKED(c_bool), POINTER(sd_net))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 825
if hasattr(_libs['SDDEKit'], 'sd_net_new_het'):
    sd_net_new_het = _libs['SDDEKit'].sd_net_new_het
    sd_net_new_het.argtypes = [c_uint32, c_uint32, POINTER(c_uint32), POINTER(c_uint32), POINTER(c_uint32), POINTER(c_uint32), POINTER(POINTER(sd_sys)), c_uint32, POINTER(c_uint32), POINTER(c_uint32), POINTER(c_double), POINTER(c_double)]
    sd_net_new_het.restype = POINTER(sd_net)

# /home/mw/dev/sddekit/src/sddekit.h: 848
if hasattr(_libs['SDDEKit'], 'sd_net_new_hom'):
    sd_net_new_hom = _libs['SDDEKit'].sd_net_new_hom
    sd_net_new_hom.argtypes = [c_uint32, POINTER(sd_sys), c_uint32, c_uint32, c_uint32, c_uint32, POINTER(c_uint32), POINTER(c_uint32), POINTER(c_double), POINTER(c_double)]
    sd_net_new_hom.restype = POINTER(sd_net)

# /home/mw/dev/sddekit/src/sddekit.h: 861
for _lib in _libs.itervalues():
    if not hasattr(_lib, 'sd_roi_new_default'):
        continue
    sd_roi_new_default = _lib.sd_roi_new_default
    sd_roi_new_default.argtypes = [c_uint32, POINTER(c_uint32)]
    sd_roi_new_default.restype = POINTER(sd_sys)
    break

# /home/mw/dev/sddekit/src/sddekit.h: 872
class struct_sd_out(Structure):
    pass

sd_out = struct_sd_out # /home/mw/dev/sddekit/src/sddekit.h: 867

struct_sd_out.__slots__ = [
    'ptr',
    'free',
    'apply',
]
struct_sd_out._fields_ = [
    ('ptr', POINTER(None)),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_out))),
    ('apply', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_out), c_double, c_uint32, POINTER(c_double), c_uint32, POINTER(c_double))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 901
if hasattr(_libs['SDDEKit'], 'sd_out_new_cb'):
    sd_out_new_cb = _libs['SDDEKit'].sd_out_new_cb
    sd_out_new_cb.argtypes = [POINTER(None), CFUNCTYPE(UNCHECKED(sd_stat), POINTER(None), c_double, c_uint32, POINTER(c_double), c_uint32, POINTER(c_double))]
    sd_out_new_cb.restype = POINTER(sd_out)

# /home/mw/dev/sddekit/src/sddekit.h: 913
class struct_sd_out_file(Structure):
    pass

sd_out_file = struct_sd_out_file # /home/mw/dev/sddekit/src/sddekit.h: 908

struct_sd_out_file.__slots__ = [
    'ptr',
    'out',
    'is_std',
    'get_fd',
]
struct_sd_out_file._fields_ = [
    ('ptr', POINTER(None)),
    ('out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_file))),
    ('is_std', CFUNCTYPE(UNCHECKED(c_bool), POINTER(sd_out_file))),
    ('get_fd', CFUNCTYPE(UNCHECKED(POINTER(FILE)), POINTER(sd_out_file))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 946
if hasattr(_libs['SDDEKit'], 'sd_out_file_new_from_name'):
    sd_out_file_new_from_name = _libs['SDDEKit'].sd_out_file_new_from_name
    sd_out_file_new_from_name.argtypes = [String]
    sd_out_file_new_from_name.restype = POINTER(sd_out_file)

# /home/mw/dev/sddekit/src/sddekit.h: 955
if hasattr(_libs['SDDEKit'], 'sd_out_file_new_from_std'):
    sd_out_file_new_from_std = _libs['SDDEKit'].sd_out_file_new_from_std
    sd_out_file_new_from_std.argtypes = [POINTER(FILE)]
    sd_out_file_new_from_std.restype = POINTER(sd_out_file)

# /home/mw/dev/sddekit/src/sddekit.h: 964
class struct_sd_out_mem(Structure):
    pass

sd_out_mem = struct_sd_out_mem # /home/mw/dev/sddekit/src/sddekit.h: 959

struct_sd_out_mem.__slots__ = [
    'ptr',
    'out',
    'get_nx',
    'get_nc',
    'get_n_sample',
    'get_capacity',
    'get_xs',
    'get_cs',
]
struct_sd_out_mem._fields_ = [
    ('ptr', POINTER(None)),
    ('out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_mem))),
    ('get_nx', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_mem))),
    ('get_nc', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_mem))),
    ('get_n_sample', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_mem))),
    ('get_capacity', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_mem))),
    ('get_xs', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_mem))),
    ('get_cs', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_mem))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1026
if hasattr(_libs['SDDEKit'], 'sd_out_mem_new'):
    sd_out_mem_new = _libs['SDDEKit'].sd_out_mem_new
    sd_out_mem_new.argtypes = []
    sd_out_mem_new.restype = POINTER(sd_out_mem)

# /home/mw/dev/sddekit/src/sddekit.h: 1035
class struct_sd_out_tee(Structure):
    pass

sd_out_tee = struct_sd_out_tee # /home/mw/dev/sddekit/src/sddekit.h: 1030

struct_sd_out_tee.__slots__ = [
    'ptr',
    'out',
    'get_nout',
    'outs_is_null',
    'set_out',
    'get_out',
]
struct_sd_out_tee._fields_ = [
    ('ptr', POINTER(None)),
    ('out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_tee))),
    ('get_nout', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_tee))),
    ('outs_is_null', CFUNCTYPE(UNCHECKED(c_bool), POINTER(sd_out_tee))),
    ('set_out', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_out_tee), c_uint32, POINTER(sd_out))),
    ('get_out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_tee), c_uint32)),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1087
if hasattr(_libs['SDDEKit'], 'sd_out_tee_new'):
    sd_out_tee_new = _libs['SDDEKit'].sd_out_tee_new
    sd_out_tee_new.argtypes = [c_uint32]
    sd_out_tee_new.restype = POINTER(sd_out_tee)

# /home/mw/dev/sddekit/src/sddekit.h: 1096
class struct_sd_out_tavg(Structure):
    pass

sd_out_tavg = struct_sd_out_tavg # /home/mw/dev/sddekit/src/sddekit.h: 1094

struct_sd_out_tavg.__slots__ = [
    'ptr',
    'out',
    'get_len',
    'get_pos',
    'get_t',
    'get_out',
    'get_x',
    'get_c',
]
struct_sd_out_tavg._fields_ = [
    ('ptr', POINTER(None)),
    ('out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_tavg))),
    ('get_len', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_tavg))),
    ('get_pos', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_tavg))),
    ('get_t', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_out_tavg))),
    ('get_out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_tavg))),
    ('get_x', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_tavg))),
    ('get_c', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_tavg))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1143
if hasattr(_libs['SDDEKit'], 'sd_out_tavg_new'):
    sd_out_tavg_new = _libs['SDDEKit'].sd_out_tavg_new
    sd_out_tavg_new.argtypes = [c_uint32, POINTER(sd_out)]
    sd_out_tavg_new.restype = POINTER(sd_out_tavg)

# /home/mw/dev/sddekit/src/sddekit.h: 1152
class struct_sd_out_sfilt(Structure):
    pass

sd_out_sfilt = struct_sd_out_sfilt # /home/mw/dev/sddekit/src/sddekit.h: 1147

struct_sd_out_sfilt.__slots__ = [
    'ptr',
    'out',
    'get_nfilt',
    'get_filtlen',
    'get_xfilts',
    'get_cfilts',
    'get_x',
    'get_c',
    'get_out',
]
struct_sd_out_sfilt._fields_ = [
    ('ptr', POINTER(None)),
    ('out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_sfilt))),
    ('get_nfilt', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_sfilt))),
    ('get_filtlen', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_out_sfilt))),
    ('get_xfilts', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_sfilt))),
    ('get_cfilts', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_sfilt))),
    ('get_x', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_sfilt))),
    ('get_c', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_out_sfilt))),
    ('get_out', CFUNCTYPE(UNCHECKED(POINTER(sd_out)), POINTER(sd_out_sfilt))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1207
if hasattr(_libs['SDDEKit'], 'sd_out_sfilt_new'):
    sd_out_sfilt_new = _libs['SDDEKit'].sd_out_sfilt_new
    sd_out_sfilt_new.argtypes = [c_uint32, c_uint32, POINTER(c_double), POINTER(c_double), POINTER(sd_out)]
    sd_out_sfilt_new.restype = POINTER(sd_out_sfilt)

# /home/mw/dev/sddekit/src/sddekit.h: 1215
if hasattr(_libs['SDDEKit'], 'sd_out_new_until'):
    sd_out_new_until = _libs['SDDEKit'].sd_out_new_until
    sd_out_new_until.argtypes = [c_double]
    sd_out_new_until.restype = POINTER(sd_out)

# /home/mw/dev/sddekit/src/sddekit.h: 1221
for _lib in _libs.itervalues():
    if not hasattr(_lib, 'sd_out_ignore'):
        continue
    sd_out_ignore = _lib.sd_out_ignore
    sd_out_ignore.argtypes = [c_bool, c_bool]
    sd_out_ignore.restype = POINTER(sd_out)
    break

# /home/mw/dev/sddekit/src/sddekit.h: 1234
class struct_sd_sch(Structure):
    pass

sd_sch = struct_sd_sch # /home/mw/dev/sddekit/src/sddekit.h: 1229

struct_sd_sch.__slots__ = [
    'ptr',
    'get_nx',
    'apply',
    'free',
]
struct_sd_sch._fields_ = [
    ('ptr', POINTER(None)),
    ('get_nx', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sch))),
    ('apply', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_sch), POINTER(sd_hist), POINTER(sd_rng), POINTER(sd_sys), c_double, c_double, c_uint32, POINTER(c_double), c_uint32, POINTER(c_double))),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sch))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1278
if hasattr(_libs['SDDEKit'], 'sd_sch_new_cb'):
    sd_sch_new_cb = _libs['SDDEKit'].sd_sch_new_cb
    sd_sch_new_cb.argtypes = [c_uint32, POINTER(None), CFUNCTYPE(UNCHECKED(sd_stat), POINTER(None), POINTER(sd_hist), POINTER(sd_rng), POINTER(sd_sys), c_double, c_double, c_uint32, POINTER(c_double), c_uint32, POINTER(c_double))]
    sd_sch_new_cb.restype = POINTER(sd_sch)

# /home/mw/dev/sddekit/src/sddekit.h: 1298
if hasattr(_libs['SDDEKit'], 'sd_sch_new_id'):
    sd_sch_new_id = _libs['SDDEKit'].sd_sch_new_id
    sd_sch_new_id.argtypes = [c_uint32]
    sd_sch_new_id.restype = POINTER(sd_sch)

# /home/mw/dev/sddekit/src/sddekit.h: 1305
if hasattr(_libs['SDDEKit'], 'sd_sch_new_em'):
    sd_sch_new_em = _libs['SDDEKit'].sd_sch_new_em
    sd_sch_new_em.argtypes = [c_uint32]
    sd_sch_new_em.restype = POINTER(sd_sch)

# /home/mw/dev/sddekit/src/sddekit.h: 1314
if hasattr(_libs['SDDEKit'], 'sd_sch_new_emc'):
    sd_sch_new_emc = _libs['SDDEKit'].sd_sch_new_emc
    sd_sch_new_emc.argtypes = [c_uint32, c_double]
    sd_sch_new_emc.restype = POINTER(sd_sch)

# /home/mw/dev/sddekit/src/sddekit.h: 1325
for _lib in _libs.itervalues():
    if not hasattr(_lib, 'sd_sch_emcolor_get_lam'):
        continue
    sd_sch_emcolor_get_lam = _lib.sd_sch_emcolor_get_lam
    sd_sch_emcolor_get_lam.argtypes = [POINTER(sd_sch)]
    sd_sch_emcolor_get_lam.restype = c_double
    break

# /home/mw/dev/sddekit/src/sddekit.h: 1332
if hasattr(_libs['SDDEKit'], 'sd_sch_new_heun'):
    sd_sch_new_heun = _libs['SDDEKit'].sd_sch_new_heun
    sd_sch_new_heun.argtypes = [c_uint32]
    sd_sch_new_heun.restype = POINTER(sd_sch)

# /home/mw/dev/sddekit/src/sddekit.h: 1349
class struct_sd_sol(Structure):
    pass

sd_sol = struct_sd_sol # /home/mw/dev/sddekit/src/sddekit.h: 1344

struct_sd_sol.__slots__ = [
    'ptr',
    'free',
    'cont',
    'get_nx',
    'get_nce',
    'get_nca',
    'get_hist',
    'get_rng',
    'get_t',
    'get_x',
    'get_c',
]
struct_sd_sol._fields_ = [
    ('ptr', POINTER(None)),
    ('free', CFUNCTYPE(UNCHECKED(None), POINTER(sd_sol))),
    ('cont', CFUNCTYPE(UNCHECKED(sd_stat), POINTER(sd_sol))),
    ('get_nx', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sol))),
    ('get_nce', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sol))),
    ('get_nca', CFUNCTYPE(UNCHECKED(c_uint32), POINTER(sd_sol))),
    ('get_hist', CFUNCTYPE(UNCHECKED(POINTER(sd_hist)), POINTER(sd_sol))),
    ('get_rng', CFUNCTYPE(UNCHECKED(POINTER(sd_rng)), POINTER(sd_sol))),
    ('get_t', CFUNCTYPE(UNCHECKED(c_double), POINTER(sd_sol))),
    ('get_x', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_sol))),
    ('get_c', CFUNCTYPE(UNCHECKED(POINTER(c_double)), POINTER(sd_sol))),
]

# /home/mw/dev/sddekit/src/sddekit.h: 1445
if hasattr(_libs['SDDEKit'], 'sd_sol_new_default'):
    sd_sol_new_default = _libs['SDDEKit'].sd_sol_new_default
    sd_sol_new_default.argtypes = [POINTER(sd_sys), POINTER(sd_sch), POINTER(sd_out), POINTER(sd_hfill), c_uint32, c_uint32, POINTER(c_double), c_uint32, c_uint32, POINTER(c_uint32), POINTER(c_double), c_double, c_double]
    sd_sol_new_default.restype = POINTER(sd_sol)

# /home/mw/dev/sddekit/src/sddekit.h: 1480
if hasattr(_libs['SDDEKit'], 'sd_sparse_from_dense'):
    sd_sparse_from_dense = _libs['SDDEKit'].sd_sparse_from_dense
    sd_sparse_from_dense.argtypes = [c_uint32, c_uint32, POINTER(c_double), POINTER(c_double), c_double, POINTER(c_uint32), POINTER(POINTER(c_uint32)), POINTER(POINTER(c_uint32)), POINTER(POINTER(c_double)), POINTER(POINTER(c_double))]
    sd_sparse_from_dense.restype = sd_stat

sd_log_msg_fp = CFUNCTYPE(UNCHECKED(c_int), String) # /home/mw/dev/sddekit/src/sddekit.h: 1497

# /home/mw/dev/sddekit/src/sddekit.h: 1499
try:
    sd_log_msg = (sd_log_msg_fp).in_dll(_libs['SDDEKit'], 'sd_log_msg')
except:
    pass

# /home/mw/dev/sddekit/src/sddekit.h: 1504
if hasattr(_libs['SDDEKit'], 'sd_log_get_msg'):
    sd_log_get_msg = _libs['SDDEKit'].sd_log_get_msg
    sd_log_get_msg.argtypes = []
    sd_log_get_msg.restype = sd_log_msg_fp

# /home/mw/dev/sddekit/src/sddekit.h: 1509
if hasattr(_libs['SDDEKit'], 'sd_log_set_msg'):
    sd_log_set_msg = _libs['SDDEKit'].sd_log_set_msg
    sd_log_set_msg.argtypes = [sd_log_msg_fp]
    sd_log_set_msg.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 1514
if hasattr(_libs['SDDEKit'], 'sd_log_is_quiet'):
    sd_log_is_quiet = _libs['SDDEKit'].sd_log_is_quiet
    sd_log_is_quiet.argtypes = []
    sd_log_is_quiet.restype = c_bool

# /home/mw/dev/sddekit/src/sddekit.h: 1519
if hasattr(_libs['SDDEKit'], 'sd_log_set_quiet'):
    sd_log_set_quiet = _libs['SDDEKit'].sd_log_set_quiet
    sd_log_set_quiet.argtypes = [c_bool]
    sd_log_set_quiet.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 1524
if hasattr(_libs['SDDEKit'], 'sd_log_is_verbose'):
    sd_log_is_verbose = _libs['SDDEKit'].sd_log_is_verbose
    sd_log_is_verbose.argtypes = []
    sd_log_is_verbose.restype = c_bool

# /home/mw/dev/sddekit/src/sddekit.h: 1529
if hasattr(_libs['SDDEKit'], 'sd_log_set_verbose'):
    sd_log_set_verbose = _libs['SDDEKit'].sd_log_set_verbose
    sd_log_set_verbose.argtypes = [c_bool]
    sd_log_set_verbose.restype = None

sd_err_handler_fp = CFUNCTYPE(UNCHECKED(None), c_int, String, c_int, String, String) # /home/mw/dev/sddekit/src/sddekit.h: 1565

# /home/mw/dev/sddekit/src/sddekit.h: 1570
if hasattr(_libs['SDDEKit'], 'sd_err_default_handler'):
    sd_err_default_handler = _libs['SDDEKit'].sd_err_default_handler
    sd_err_default_handler.argtypes = [c_int, String, c_int, String, String]
    sd_err_default_handler.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 1575
if hasattr(_libs['SDDEKit'], 'sd_err_get_handler'):
    sd_err_get_handler = _libs['SDDEKit'].sd_err_get_handler
    sd_err_get_handler.argtypes = []
    sd_err_get_handler.restype = sd_err_handler_fp

# /home/mw/dev/sddekit/src/sddekit.h: 1582
if hasattr(_libs['SDDEKit'], 'sd_err_set_handler'):
    sd_err_set_handler = _libs['SDDEKit'].sd_err_set_handler
    sd_err_set_handler.argtypes = [sd_err_handler_fp]
    sd_err_set_handler.restype = None

# /home/mw/dev/sddekit/src/sddekit.h: 1587
if hasattr(_libs['SDDEKit'], 'sd_err_handler'):
    sd_err_handler = _libs['SDDEKit'].sd_err_handler
    sd_err_handler.argtypes = [c_int, String, c_int, String, String]
    sd_err_handler.restype = None

sd_rng = struct_sd_rng # /home/mw/dev/sddekit/src/sddekit.h: 112

sd_hfill = struct_sd_hfill # /home/mw/dev/sddekit/src/sddekit.h: 159

sd_hist = struct_sd_hist # /home/mw/dev/sddekit/src/sddekit.h: 197

sd_sys_in = struct_sd_sys_in # /home/mw/dev/sddekit/src/sddekit.h: 458

sd_sys_out = struct_sd_sys_out # /home/mw/dev/sddekit/src/sddekit.h: 462

sd_sys = struct_sd_sys # /home/mw/dev/sddekit/src/sddekit.h: 470

sd_sys_exc = struct_sd_sys_exc # /home/mw/dev/sddekit/src/sddekit.h: 533

sd_net = struct_sd_net # /home/mw/dev/sddekit/src/sddekit.h: 649

sd_out = struct_sd_out # /home/mw/dev/sddekit/src/sddekit.h: 872

sd_out_file = struct_sd_out_file # /home/mw/dev/sddekit/src/sddekit.h: 913

sd_out_mem = struct_sd_out_mem # /home/mw/dev/sddekit/src/sddekit.h: 964

sd_out_tee = struct_sd_out_tee # /home/mw/dev/sddekit/src/sddekit.h: 1035

sd_out_tavg = struct_sd_out_tavg # /home/mw/dev/sddekit/src/sddekit.h: 1096

sd_out_sfilt = struct_sd_out_sfilt # /home/mw/dev/sddekit/src/sddekit.h: 1152

sd_sch = struct_sd_sch # /home/mw/dev/sddekit/src/sddekit.h: 1234

sd_sol = struct_sd_sol # /home/mw/dev/sddekit/src/sddekit.h: 1349

# No inserted files

