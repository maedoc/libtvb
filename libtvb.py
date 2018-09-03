# copyright 2016 Apache 2 libtvb authors

import ctypes
import logging

logging.basicConfig(level=logging.DEBUG)
LOG = logging.getLogger('libtvb')
LIB_NAME = './libtvb.so'
LOG.info("using shared library %r" % (LIB_NAME, ))
LIB = ctypes.CDLL(LIB_NAME)

# common data types
u32, f64 = ctypes.c_uint32, ctypes.c_double
u32p, f64p = ctypes.POINTER(u32), ctypes.POINTER(f64)

def make_enum(name, member_names): # {{{
	members = {}
	for i, member in enumerate(members):
		members[member] = ctypes.c_uint(i)
	def repr(self):
		return self.member_names[self.value]
	def eq(self, other):
		return self.value == other.value
	enum_class = type(name, (ctypes.c_uint, ), {
		'members': members,
		'member_names': member_names[:],
		'__repr__': repr,
		'__eq__': eq
	})
	for i, member in enumerate(member_names):
		setattr(enum_class, member, enum_class(i))
	return enum_class
#}}}

def make_func(name, restype=None, *argtypes): #{{{
	fn = getattr(LIB, name)
	fn.restype = restype
	fn.argtypes = list(argtypes)
	return fn
#}}}

tvb_stat = make_enum('tvb_stat',
	'OK ERR CONT STOP UKNOWN ZERO NON_ZERO OUT_OF_BOUNDS'.split(' '))

# util/ver.h {{{
tvb_ver_major = make_func('tvb_ver_major', ctypes.c_uint32)
tvb_ver_minor = make_func('tvb_ver_minor', ctypes.c_uint32)
#}}}

# util/malloc.h {{{
tvb_malloc_reg_init = make_func('tvb_malloc_reg_init')
tvb_malloc_reg_stop = make_func('tvb_malloc_reg_stop')
tvb_malloc_reg_query = make_func('tvb_malloc_reg_query', tvb_stat, ctypes.c_void_p)
tvb_malloc_total_nbytes = make_func('tvb_malloc_total_nbytes', ctypes.c_uint32)
#}}}

# util/log.h {{{
tvb_log_level = make_enum('tvb_log_level', 'ERROR INFO DEBUG'.split(' '))
tvb_log_handler = ctypes.CFUNCTYPE(None, tvb_log_level, ctypes.c_char_p)
tvb_log_set_handler = make_func('tvb_log_set_handler', None, tvb_log_handler)
tvb_log_get_handler = make_func('tvb_log_get_handler', tvb_log_handler)
tvb_log_get_err_and_reset = make_func('tvb_log_get_err_and_reset', ctypes.c_bool)

class libtvbException(Exception): pass

@tvb_log_handler
def handler(level, message):
	if level == tvb_log_level.DEBUG:
		LOG.debug(message)
	elif level == tvb_log_level.INFO:
		LOG.info(message)
	elif level == tvb_log_level.ERROR:
		handler.last_error_message = message
		LOG.error(message)
	else:
		fmt = 'unhandled libtvb log level %r for message %r'
		LOG.warn(fmt, level, message)

def check_and_raise():
	if tvb_log_get_err_and_reset():
		raise libtvbException(handler.last_error_message)

tvb_log_set_handler(handler)
#}}}

# util/interface_macros.h {{{
def _common_fields(type):
	ptr = ctypes.POINTER(type)
	fp = ctypes.CFUNCTYPE
	return [
		('data', ctypes.c_void_p),
		('copy', fp(ptr, ptr)),
		('n_byte', fp(u32, ptr)),
		('free', fp(None, ptr))
	]

def make_fp_members(struct, *members):
	_fields_ = _common_fields(struct.__name__)
	ptr = ctypes.POINTER(struct)
	for name, sig in members:
		sig = (sig[0], ptr) + sig[1:]
		_fields_.append((name, ctypes.CFUNCTYPE(*sig)))
	struct._fields_ = _fields_

def make_struct(name, *members):
	struct = type(name, (ctypes.Structure, ), {})
	make_fp_members(struct, *members)
	return struct
#}}}

# conn/base.h {{{
tvb_conn = make_struct('tvb_conn',
	('row_wise_weighted_sum', (None, f64p, f64p)),
	('get_n_nonzeros', (u32, )),
	('get_nonzero_indices', (u32p, )),
	('get_weights', (f64p, )),
	('get_delays', (f64p, )),
	('get_delay_scale', (f64, )),
	('set_delay_scale', (tvb_stat, f64)),
	('get_n_row', (u32, )),
	('get_n_col', (u32, ))
)

tvb_conn_p = ctypes.POINTER(tvb_conn)

tvb_conn_new_sparse = make_func('tvb_conn_new_sparse',
	tvb_conn_p, u32, u32, u32, u32p, u32p, f64p, f64p)

tvb_conn_new_dense = make_func('tvb_conn_new_dense',
	tvb_conn_p, u32, u32, f64p, f64p)

#}}}

def ndf64p(array):
	return array.ctypes.data_as(f64p)

# def make_class(struct, *args):
# 	attrs = {}
# 	@classmethod
# 	def new_dense(cls, W, D):
# 		obj = cls()
# 		n = len(W)
# 		obj._ptr = tvb_conn_new_dense(n, n, ndf64p(W), ndf64p(D))
# 		check_and_raise()
# 		return obj
# 	attrs['new_dense'] = new_dense
# 	for name, fp in struct._fields_:
# 		def wrap(self, *args):

LOG.debug('libtvb API built')

import numpy as np
W = np.random.randn(50, 50)
W = (W > 2.0) * W
D = np.ones((50, 50))
conn = tvb_conn_new_dense(50, 50, W.ctypes.data_as(f64p), D.ctypes.data_as(f64p))
c = conn.contents
scale = 42.42
assert c.set_delay_scale(conn, scale) == tvb_stat.OK
assert c.get_delay_scale(conn) == scale
assert c.get_n_row(conn) == 50 and c.get_n_col(conn) == 50
assert c.get_n_nonzeros(conn) == (W!=0.0).sum()

print c.set_delay_scale(conn, -42.42)
check_and_raise()

# vim: foldmethod=marker
