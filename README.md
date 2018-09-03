# libtvb 

libtvb is a C rewrite and generalization of numerical algorithms
backing the simulator of [The Virtual Brain](http://thevirtualbrain.org)
project, targeting usage as 

- new backend for TVB's Python framework & library
- cosimulation w/ other simulation frameworks
- parameter sweeps for accelerators
- model inversion

## Usage

```bash
make -j
python libtvb.py
```

See `lib/bench/*` for some examples.