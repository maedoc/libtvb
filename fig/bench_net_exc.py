# copyright 2016 Apache 2 sddekit authors

import numpy as np
import pylab as pl

dat = np.loadtxt('bench_net_exc.dat')
x, y = np.transpose(dat[:, 2:-1].reshape((-1, 76, 2)), (2, 0, 1))

pl.figure(figsize=(8, 3))
pl.imshow(x.T, aspect='auto')
pl.xlabel('Time (steps)')
pl.colorbar()
pl.savefig('bench_net_exc.png')
