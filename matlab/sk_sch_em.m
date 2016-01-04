classdef sk_sch_em < sk_ptr
    % Euler-Maruyama integration scheme.
    %
    % copyright 2016 Apache 2 sddekit authors
    
    properties(Dependent)
        nx % number of state variables
    end
    
    methods
        function obj = sk_sch_em(arg)
            ptr = [];
            init_from_ptr = isa(class(arg), 'uint64');
            if init_from_ptr
                ptr = arg;
            end
            obj = obj@sk_ptr(ptr);
            if ~init_from_ptr
                obj.mex('init', arg)
            end
        end
        
        function nx = get.nx(obj)
            nx = obj.mex('get_nx');
        end
        
        function [x, c, sys] = apply(obj, hist, rng, sys, t, dt, x)
            % apply Apply this integration scheme to arguments
            %
            % Input Arguments
            % 
            % - hist - an instance of sk_hist
            % - rng - instance of rk_state
            % - sys - system to apply integration scheme to
            % - t - current time
            % - dt - time step
            % - x - current state vector
            %
            % Returns
            % 
            % - x - updated state
            % - c - output variables of system
            % - sys - system struct (possibly updated)
            
            % TODO: signature is wrong: there would be no c input, and we
            % and the mex cb should allocate c size nd before sk_sch_em
            % gets from the history. on output, should be size whatever the
            % system defines it to be, but atleast maxvi.
            [x, c, sys] = obj.mex('apply', hist, rng, sys, t, dt, x);
        end
    end
end 
