classdef sk_hist < sk_ptr
    % sk_hist History
    %
    % copyright 2016 Apache 2 sddekit authors
    
    properties(Dependent)
        nd % number of delays
        nu % number of unique variable indices
        maxvi % maximum variable index
        t % get current time in history buffer
        dt % get internal time step of history buffer
    end
    
    methods
        function obj = sk_hist(vi, vd, t0, dt)
            ptr = [];
            if nargin == 1 && isa(vi, 'uint64')
                ptr = vi;
            end
            obj = obj@sk_ptr(ptr);
            if nargin > 1
                if numel(vi)~=numel(vd)
                    error('vi & vd must have same number of elements');
                end
                obj.mex('init', uint64(vi(:)), double(vd(:)), t0, dt);
            end
        end

        function fill(obj, hf)
            % fill Fill history buffer.
            %
            % hf should be a struct with at least one field 'f' which 
            % has signature buf = f(hf, t, i), where t & i are vectors
            % of time points < t0 & corresponding variable indices.
            % f should return the values of variables for those times.
            %
            % As convenience, if hf is not a struct, it may be a function
            % name or function handle.
            if ~isstruct(hf)
                hf = struct('f', hf);
            end
            obj.mex('fill', hf);
        end

        function out = get(obj, t)
            out = obj.mex('get', t);
        end

        function set(obj, t, x)
            obj.mex('set', t, x(:));
        end

        function out = get.maxvi(obj)
            out = obj.mex('get_maxvi');
        end

        function out = vi2i(obj, i)
            out = obj.mex('get_vi2i', i);
        end

        function out = get.nu(obj)
            out = obj.mex('get_nu');
        end

        function out = buf_lin(obj, i)
            out = obj.mex('get_buf_lin', i);
        end

        function out = get.nd(obj)
            out = obj.mex('get_nd');
        end

        function out = get.t(obj)
            out = obj.mex('get_t');
        end

        function out = get.dt(obj)
            out = obj.mex('get_dt');
        end

        function out = lim(obj, i)
            out = obj.mex('get_lim', i);
        end

        function out = len(obj, i)
            out = obj.mex('get_len', i);
        end

        function out = pos(obj, i)
            out = obj.mex('get_pos', i);
        end

        function out = uvi(obj, i)
            out = obj.mex('get_uvi', i);
        end

        function out = maxd(obj, i)
            out = obj.mex('get_maxd', i);
        end

        function out = vi(obj, i)
            out = obj.mex('get_vi', i);
        end

        function out = vd(obj, i)
            out = obj.mex('get_vd', i);
        end

    end
end 
