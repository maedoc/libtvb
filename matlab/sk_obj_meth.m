function h = sk_obj_meth(obj, meth)
% sk_obj_meth Get function handle for object method.
%
% copyright 2016 Apache 2 sddekit authors

h = eval(['@obj.' meth]);
