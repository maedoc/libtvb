function sk_mex_compile
% sk_mex_compile Compile MEX gateway to SDDEKit
%
% copyright 2016 Apache 2 sddekit authors

%%
cfiles = {'malloc' 'log' 'err' 'solv' 'hist' 'util' 'scheme'};
cfiles = cellfun(@(s) ['src/sk_' s '.c'], cfiles, 'UniformOutput', false);
cfiles = {cfiles{:} 'src/randomkit.c'};
mexcfiles = {'cb' 'main' 'util' 'wplut'};
mexcfiles = cellfun(@(s) ['matlab/private/' s '.c'], mexcfiles, 'UniformOutput', false);
flags = {'-v' '-g' '-Iinclude'};
margs = {flags{:} mexcfiles{:} cfiles{:}};
%% regular
mex(margs{:})
!mv cb.mexa64 matlab/private/sk_mex_gateway.mexa64
%%
%gateway
