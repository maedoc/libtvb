from pprint import pprint
import api
reload(api)

def dump_ast(node):
	return {'class': node.__class__.__name__,
		'attrs': {key: getattr(node, key) for key in node.attr_names},
		'children': {name: dump_ast(child)
			for name, child in node.children()}}

class Enums(api.App):
	def __init__(self):
		self.enums = {}
	def visit_Enum(self, node):
		self.enums[node.name] = []
		(_, elist), = node.children()
		for _, val in elist.children():
			self.enums[node.name].append(val.name)

class Structs(api.VisitStructFields):

	def __init__(self):
		super(Structs, self).__init__()
		self.structs = {}

	def _add_field(self, field, replace_last=False):
		struct_name = self.struct_name[-1]
		if struct_name not in self.structs:
			self.structs[struct_name] = []
		self.structs[struct_name].append(field)

	def visit_FuncDecl(self, node):
		if self.struct:
			self._add_field(api.FuncInfo.apply(node))

sv = Structs.apply(ast)
