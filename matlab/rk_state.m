classdef rk_state < sk_ptr
    % rk_state Random number generator state
    %
    % copyright 2016 Apache 2 sddekit authors
    
    properties(Dependent)
        seed
    end
    
    methods
        function obj = rk_state(ptr, seed)
            p = [];
            if nargin > 0 && isa(p, 'uint64')
                p = ptr;
            end
            obj = obj@sk_ptr(p);
            if nargin < 2
                obj.seed = 42;
            elseif ~isempty(seed)
                obj.seed = seed;
            end
        end
        
        function set.seed(obj, seed)
            obj.mex('seed', seed);
        end
        
        function rn = gauss(obj)
            rn = obj.mex('gauss');
        end

    end    
end 