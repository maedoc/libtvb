classdef sk_solv < sk_ptr
    % sk_solv Solver
    %
    % copyright 2016 Apache 2 sddekit authors
    
    properties (Dependent)
        rng
        hist
        nx
        nc
        t
        x
        c
    end
    
    methods
        function obj = sk_solv(varargin)
            if nargin == 1
                ptr = varargin{1};
            else
                ptr = [];
            end
            obj = obj@sk_ptr(ptr);
            if nargin > 1
                % convert sys, sch, out, hf to structs if necessary
                args = {varargin{:}};
                for i=2:5
                    if ~isstruct(args{i})
                        args{i} = struct('f', @args{i}.apply);
                    end
                end
                obj.mex('init', args{:});
            end
        end
        
        function rng = get.rng(obj)
            rng = obj.mex('get_rng');
        end
        
        function hist = get.hist(obj)
            hist = obj.mex('get_hist');
        end

        function cont(obj)
            obj.mex('cont')
        end

        function nx = get.nx(obj)
            nx = obj.mex('get_nx')
        end

        function nc = get.nc(obj)
            nc = obj.mex('get_nc')
        end

        function t = get.t(obj)
            t = obj.mex('get_t')
        end

        function x = get.x(obj)
            x = obj.mex('get_x')
        end

        function c = get.c(obj)
            c = obj.mex('get_c')
        end

    end
end
