# copyright 2016 Apache 2 libtvb authors

"""
This module implements visitors for extracting SDDEKit's API
from pycparser's parse tree of SDDEKit's header.

"""

import collections
import pycparser

class BaseVisitor(pycparser.c_ast.NodeVisitor):
    """
    Subclass of NodeVisitor with simple class method to build instance,
    visit a given node, and return instance.

    """

    @classmethod
    def apply(cls, node):
        obj = cls()
        obj.visit(node)
        return obj


class TypeInfo(BaseVisitor):
    "Visits a type to extract it's pointer level, declaration name and type."

    def __init__(self):
        self.ptr = 0
        self.name = ''
        self.typenames = ''

    def visit_PtrDecl(self, node):
        self.ptr += 1
        self.generic_visit(node)

    def visit_TypeDecl(self, node):
        self.name = node.declname
        self.generic_visit(node)

    def visit_IdentifierType(self, node):
        self.typenames = ' '.join(node.names)


class FuncInfo(BaseVisitor):
    "Visits a function declaration to extract name, result and argument types."

    def __init__(self):
        self.restype = None
        self.name = ''
        self.argtypes = []

    def visit_FuncDecl(self, node):
        self.restype = TypeInfo.apply(node.type)
        self.name = self.restype.name
        self.argtypes = [TypeInfo.apply(child) for _, child in node.args.children()]


class MethodsVisitor(BaseVisitor):
    """
    Visits function pointers which are fields of structs.

    This will not do anything by itself, but should probably be subclassed
    with a visit_FuncDecl method to do something with the resulting
    function pointer declarations.

    """

    def __init__(self):
        self.struct = 0
        self.ptr = 0
        self.typedef = False
        self.struct_name = []

    def visit_Typedef(self, node):
        self.typedef = True
        self.generic_visit(node)
        self.typedef = False

    def visit_PtrDecl(self, node):
        self.ptr += 1
        self.generic_visit(node)
        self.ptr -= 1

    def visit_Struct(self, node):
        self.struct += 1
        self.struct_name.append(node.name)
        if not self.typedef:
            self.generic_visit(node)
        self.struct_name.pop()
        self.struct -= 1


class InterfaceMethods(MethodsVisitor):

    Method = collections.namedtuple('Method',
        'restype struct_name field_name arg_types arg_names'.split())
    
    def  __init__(self):
        super(InterfaceMethods, self).__init__()
        self.interfaces = {}
    
    def _add_method(self, method):
        struct_name = self.struct_name[-1]
        if method.struct_name not in self.interfaces:
            self.interfaces[method.struct_name] = []
        self.interfaces[method.struct_name].append(method)

    def visit_FuncDecl(self, node):
        if self.struct and self.ptr:
            fi = FuncInfo.apply(node)
            arg_names, arg_types = [], []
            for i, arg in enumerate(fi.argtypes):
                arg_names.append('a%d' % (i, )) # TODO
                arg_types.append((arg.typenames, arg.ptr))
            method = self.Method(
                restype=fi.restype.typenames + ('*' * fi.restype.ptr),
                struct_name=self.struct_name[-1],
                field_name=fi.name,
                arg_types=arg_types,
                arg_names=arg_names
            )
            self._add_method(method)


class Enums(BaseVisitor):

    def __init__(self):
        super(Enums, self).__init__()
        self.enums = {}

    def visit_Enum(self, node):
        if node.name not in self.enums:
            self.enums[node.name] = []
        children = node.children()
        if children:
            (_, elist), = children
            for _, val in elist.children():
                self.enums[node.name].append(val.name)


import dev.api.preprocess
api = dev.api.preprocess.header_ast()
for method in InterfaceMethods.apply(api).interfaces['tvb_hist']:
    print (method)
