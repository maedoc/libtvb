classdef foo < handle
    properties
        iters
    end
    properties(Access=private)
        ptr
        has_been_deleted
    end
    methods
        function obj = foo()
            obj.ptr = foo_('new');
            obj.has_been_deleted = 0;
        end
        
        function iters = get.iters(obj)
            % get the number of iterations on foo obj
            iters = foo_('get_iters', obj.ptr);
        end
        
        function obj = set.iters(obj, new_iters)
            % set the num...
            foo_('set_iters', obj.ptr, new_iters);
        end
        
        function delete(obj)
            % avoid double frees
            if ~obj.has_been_deleted
                foo_('del', obj.ptr);
                obj.has_been_deleted = 1;
            end
        end
        
        function obj = manip_iters(obj, f, d)
            foo_('manip_iters', obj.ptr, f, d);
        end

	function obj = manip_array(obj, f, d)
            foo_('manip_array', obj.ptr, f, d);
	end
        
    end
end     
