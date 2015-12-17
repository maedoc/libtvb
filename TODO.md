# todo

report issues here by pull request.

## immediate

x reorg src/ include/ test/
x rework interpretation of c in/out
x add restrict everywhere
x network sys (connectivity, heterogeneous model sets & couplings)
x out fn spatio temporal filtering, plain file binary/ascii, in-mem buffer
x (REJECTED) models loop over nx as appropriate (too complicated)
x model knows its index within overall system (for e.g. spatial parameters)

- tvb models
- bindings Java/R/Py/MATLAB
- impl Jf Jg Jc (they are placeholders for now), scheme (taylor o(2) / llmult), tests (sparse jac)
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
- solv deleg common cases to dedicated code path (if profiling says it make sense!)
- allow specializations to SDE, ignoring delays, idem for DDE, ignore g
- sort net.M to evaluate models block-wise 
- specialize out sfilt handle differet nfilt for x & c
- specialize hist for integer delay case (use gist impl)
- hist linear interp, cache lookup vector between time steps

## software engineering

- move this todo to jira
x const correctness (not really a thing in c)
- move to cmake (cython: github.com/thewtex/cython-cmake-example)
- convert makefile to premake / cmake, adhoc stuff to python script
- use py/matlab/java test frameworks over bindings
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

- mingw/vim not satisfactory on windows

## ocl

- #include existing math into cl kernels

## cli

- e.g. ./sk --jr --emcolor --tf 1e3 --conn cocomac.h5
- separate config, needs hdf5 etc
