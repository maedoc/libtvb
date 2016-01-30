%% load library
% On 64-bit platforms this involves generate a 'thunk' dll which contains
% a C function per function signature. Likely this needs to be distributed
% to avoid requiring compiling on user's machine. Upside is that it can
% with lib dll so minor upgrades can just switch the dll file.

loadlibrary('../libSDDEKit.so', 'sddekit.h')

%% see a list of available functions & signatures
libfunctionsview('libSDDEKit')

%% construct an rng object
rng = calllib('libSDDEKit', 'sd_rng_new_default');

%% seed the rng
calllib('libSDDEKit', 'sd_rng_seed', rng, 42)

%% fill an array. NB don't use the ptr output otherwise segfault
[~, z] = calllib('libSDDEKit', 'sd_rng_fill_norm', rng, 10, z);
