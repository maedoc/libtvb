import sys
sys.path.append('build/lib.linux-x86_64-2.7')
import pylib

def f(x):
	print x
	return x*2.3 + 0.0234

print pylib.pyfunc(f, 3.3)

def g(x):
	print x.sum()
	x[:] += 1.2
	print x.sum()

pylib.pyfunc2(g)
