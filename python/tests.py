# copyright 2016 Apache 2 sddekit authors

import sys
import glob
import unittest
import numpy as np

sys.path.append(glob.glob('./build/lib*')[0])
print ("added %r to path for built sddekit module" % (sys.path[-1], ))
import hist as sk

class TestHist(unittest.TestCase):
    def test_basic(self):
        dt = 0.1
        vi = np.r_[1, 1, 0, 0].astype(np.uint32)
        vd = np.r_[5.5, 4.5, 33.3, 0.0] * dt
        h = sk.Hist(vi, vd, 0.0, dt)
        self.assertEqual(4, h.nd())
        self.assertEqual(4, h.nd())
        self.assertEqual(0.0, h.t())
        self.assertEqual(dt, h.dt())
        self.assertEqual(2, h.nu())
        self.assertEqual(0, h.lim(0))
        self.assertEqual(36, h.lim(1))
        self.assertEqual(8 + 36, h.lim(2))
        self.assertEqual(36, h.len(0))
        self.assertEqual(8, h.len(1))
        self.assertEqual(0, h.pos(0))
        self.assertEqual(0, h.pos(1))
        self.assertEqual(0, h.uvi(0))
        self.assertEqual(1, h.uvi(1))
        self.assertEqual(1, h.maxvi())
        self.assertEqual(0, h.vi2i(0))
        self.assertEqual(1, h.vi2i(1))
        self.assertEqual(vd[0], h.maxd(1))
        self.assertEqual(vd[2], h.maxd(0))
        self.assertEqual(1, h.vi(0))
        self.assertEqual(1, h.vi(1))
        self.assertEqual(0, h.vi(2))
        self.assertEqual(0, h.vi(3))
        self.assertEqual(vd[0], h.vd(0))
        self.assertEqual(vd[1], h.vd(1))
        self.assertEqual(vd[2], h.vd(2))
        self.assertEqual(vd[3], h.vd(3))
        
        h.fill(lambda t, i: t) # user shouldn't retain ref, must copy
        for i in range(35):
            self.assertEqual(-i*dt, h.buf_lin(i))
        self.assertEqual(dt, h.buf_lin(35))
        for i in range(7):
            self.assertEqual(-i*dt, h.buf_lin(36 + i))
        self.assertEqual(dt, h.buf_lin(36 + 7))

        x = h.get(dt/3)
        self.assertTrue(np.allclose(x, -vd+dt/3))

        x[0] = 1.5
        x[1] = 1.0
        h.set(dt/2.0, x)
        self.assertTrue(np.allclose(h.buf_lin(35), 3.0))
        self.assertTrue(np.allclose(h.buf_lin(36 + 7), 2.0))

if __name__ == '__main__':
    unittest.main()
