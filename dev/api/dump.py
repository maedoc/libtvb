# copyright 2016 Apache 2 sddekit authors

"""
This module provides facilities for recursively converting pycparser
nodes into dicts or other formats such as json.

"""

def dump_ast(node):
	return {'class': node.__class__.__name__,
		'attrs': {key: getattr(node, key) for key in node.attr_names},
		'children': {name: dump_ast(child)
			for name, child in node.children()}}

# TODO json