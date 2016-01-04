classdef sk_ptr < handle
    % common code for handling pointers to sddekit objects
    %
    % copyright 2016 Apache 2 sddekit authors
        
    properties (Access = private)
        ptr
        owned
        type = '';
    end
    
    methods (Access = protected)
        function obj = sk_ptr(ptr, owned, type)
            if nargin < 3
                ds = dbstack;
                caller = strsplit(ds(2).name, '.');
                obj.type = caller{2};
            else
                obj.type = type;
            end
            if nargin < 1 || isempty(ptr)
                obj.ptr = sk_mex_gateway(obj.type, 'alloc');
                obj.owned = true;
            else
                obj.ptr = ptr;
                if nargin < 2
                    obj.owned = false;
                else
                    obj.owned = owned;
                end
            end
        end
        
        function varargout = mex(obj, meth, varargin)
            if obj.ptr ~= 0
                args = {obj.type meth obj.ptr varargin{:}};
                if nargout==0
                	sk_mex_gateway(args{:});
                    varargout = {};
                else                    
                    if nargout == 1
                	out = sk_mex_gateway(args{:});
                        varargout = {out};
                    else
                        % force explicit number of outs for mex gateway
                        outs = strjoin(arrayfun(@(i) sprintf('o%d', i), ...
                                                1:nargout, 'UniformOutput', false), ',');
                        fmt = '[%s] = sk_mex_gateway(args{:});'
                        eval(sprintf(fmt, outs));
                        varargout = eval(sprintf('{%s}', outs));
                    end
                end
            else
                error('sk:null', ...
                    'cowardly refusing pass a NULL pointer to C.');
            end
        end
        
        function delete(obj)
            if obj.ptr ~= 0 && obj.owned
                sk_mex_gateway(obj.type, 'free', obj.ptr);
                obj.ptr = 0;
            end
        end
    end

    methods
        function ptr = get_ptr(obj)
            ptr = obj.ptr;
        end
    end

end
