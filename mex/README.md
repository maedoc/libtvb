# mex bindings

Here we have basic layout for binding to sddekit C from MATLAB using a 
MEX gateway & MATLAB classdefs. Importantly, callbacks to globally defined
MATLAB functions can be handled and appear quick enough (43k calls / s in 
R2015b on 2.7 GHz i7).

Building for MATLAB can be done by locating the include directory, a list
of source files & the gateway file and passing it all to `mex`.
