# copyright 2016 Apache 2 sddekit authors

import sys
import glob
import unittest
import numpy as np
import ctypes
from sddekit import Hist

class TestHist(unittest.TestCase):
    def test_basic(self):
        dt = 0.1
        vi = np.r_[1, 1, 0, 0].astype(np.uint32)
        vd = np.r_[5.5, 4.5, 33.3, 0.0] * dt
        h = Hist(vi, vd, 0.0, dt)
        self.assertEqual(4, h.get_nd())
        self.assertEqual(0.0, h.get_t())
        self.assertEqual(dt, h.get_dt())
        self.assertEqual(2, h.get_nu())
        self.assertEqual(0, h.get_lim(0))
        self.assertEqual(36, h.get_lim(1))
        self.assertEqual(8 + 36, h.get_lim(2))
        self.assertEqual(36, h.get_len(0))
        self.assertEqual(8, h.get_len(1))
        self.assertEqual(0, h.get_pos(0))
        self.assertEqual(0, h.get_pos(1))
        self.assertEqual(0, h.get_uvi(0))
        self.assertEqual(1, h.get_uvi(1))
        self.assertEqual(1, h.get_maxvi())
        self.assertEqual(0, h.get_vi2i(0))
        self.assertEqual(1, h.get_vi2i(1))
        self.assertEqual(vd[0], h.get_maxd(1))
        self.assertEqual(vd[2], h.get_maxd(0))
        self.assertEqual(1, h.get_vi(0))
        self.assertEqual(1, h.get_vi(1))
        self.assertEqual(0, h.get_vi(2))
        self.assertEqual(0, h.get_vi(3))
        self.assertEqual(vd[0], h.get_vd(0))
        self.assertEqual(vd[1], h.get_vd(1))
        self.assertEqual(vd[2], h.get_vd(2))
        self.assertEqual(vd[3], h.get_vd(3))
        return
        
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

# vim: sw=4 et foldmethod=marker
