# copyright 2016 Apache 2 sddekit authors

import ctypes
import logging

logging.basicConfig(level=logging.DEBUG)
LOG = logging.getLogger('SDDEKit')
LIB_NAME = 'build/libSDDEKit.so'
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

sd_stat = make_enum('sd_stat',
	'OK ERR CONT STOP UKNOWN ZERO NON_ZERO OUT_OF_BOUNDS'.split(' '))

# util/ver.h {{{
sd_ver_major = make_func('sd_ver_major', ctypes.c_uint32)
sd_ver_minor = make_func('sd_ver_minor', ctypes.c_uint32)
#}}}

# util/malloc.h {{{
sd_malloc_reg_init = make_func('sd_malloc_reg_init')
sd_malloc_reg_stop = make_func('sd_malloc_reg_stop')
sd_malloc_reg_query = make_func('sd_malloc_reg_query', sd_stat, ctypes.c_void_p)
sd_malloc_total_nbytes = make_func('sd_malloc_total_nbytes', ctypes.c_uint32)
#}}}

# util/log.h {{{
sd_log_level = make_enum('sd_log_level', 'ERROR INFO DEBUG'.split(' '))
sd_log_handler = ctypes.CFUNCTYPE(None, sd_log_level, ctypes.c_char_p)
sd_log_set_handler = make_func('sd_log_set_handler', None, sd_log_handler)
sd_log_get_handler = make_func('sd_log_get_handler', sd_log_handler)

@sd_log_handler
def handler(level, message):
	if level == sd_log_level.DEBUG:
		LOG.debug(message)
	elif level == sd_log_level.INFO:
		LOG.info(message)
	elif level == sd_log_level.ERROR:
		LOG.error(message)
		raise Exception(message)
	else:
		fmt = 'unhandled SDDEKit log level %r for message %r'
		LOG.warn(fmt, level, message)


sd_log_set_handler(handler)
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
sd_conn = make_struct('sd_conn',
	('row_wise_weighted_sum', (None, f64p, f64p)),
	('get_n_nonzeros', (u32, )),
	('get_nonzero_indices', (u32p, )),
	('get_weights', (f64p, )),
	('get_delays', (f64p, )),
	('get_delay_scale', (f64, )),
	('set_delay_scale', (sd_stat, f64)),
	('get_n_row', (u32, )),
	('get_n_col', (u32, ))
)

sd_conn_p = ctypes.POINTER(sd_conn)

sd_conn_new_sparse = make_func('sd_conn_new_sparse',
	sd_conn_p, u32, u32, u32, u32p, u32p, f64p, f64p)

sd_conn_new_dense = make_func('sd_conn_new_dense',
	sd_conn_p, u32, u32, f64p, f64p)

#}}}

import numpy as np
W = np.random.randn(50, 50)
W = (W > 2.0) * W
D = np.ones((50, 50))
conn = sd_conn_new_dense(50, 50, W.ctypes.data_as(f64p), D.ctypes.data_as(f64p))
c = conn.contents
scale = 42.42
assert c.set_delay_scale(conn, scale) == sd_stat.OK
assert c.get_delay_scale(conn) == scale
assert c.get_n_row(conn) == 50 and c.get_n_col(conn) == 50
assert c.get_n_nonzeros(conn) == (W!=0.0).sum()

print c.set_delay_scale(conn, -42.42)

# vim: foldmethod=marker
