# todo

report issues here by pull request.

## needed yesterday

x reorg src/ include/ test/
x rework interpretation of c in/out
x add restrict everywhere
x (REJECTED) models loop over nx as appropriate (too complicated)
x network sys (connectivity, heterogeneous model sets & couplings)
- out fn spatio temporal filtering, plain file binary/ascii, in-mem buffer
- impl Jf Jg Jc (they are placeholders for now), scheme (taylor o(2) / llmult), tests (sparse jac)
- bindings Java/R/Py/MATLAB
- provide finite diff scheme
- general temporal filter

## verification & validation

stability, convergence, memory, speed, etc. we should generate a table
with rows per system, cols per method, and fill in statistics

x exact history test from TVB
- cover history with more difficult cases (double updates, etc)
- implement a few favorite sys (gen2Dosc, epileptor, jansenrit)
- e.g. convergence test systems from Biscay et al
- LL DDE tests from Jimenez  2006
- test problems from Kuechler Platen 2000 references (page 1)
- convert test collector to makefile
- lorenz chaos, test lyapunov expo 
- test main --test-name --test --bench (if whole suite gets too slow)
- drift & diffusion integrals can be handled independently?

## opt

- eval randn only for nnz g? test w/ benchmark
- allow specializations to SDE, ignoring delays, idem for DDE, ignore g
- sort net.M to evaluate models block-wise 
- specialize out sfilt handle differet nfilt for x & c

## software engineering

- const correctness?
- consistently memcpy inputs during init to make easier bindings
  to dynamic langs which may dealloc param arrays (free after of course).
- error handler system like GSL
- test malloc fails a la http://stackoverflow.com/questions/3868716
- add lint checks to lint.sh (e.g. all allocations use MALLOCHECK)
- hide structs into opaque pointers, impl get/set methods
x doxygen
- coverage
- profiling / benchmarks
- {cache, call}grind
- test gcc profile guided optimizations?
- emscripten for web js page (llvm dragonegg for fortran code)

## ocl

- #include existing math into cl kernels

## cli

- e.g. ./sk --jr --emcolor --tf 1e3 --conn cocomac.h5
- separate config, needs hdf5 etc
