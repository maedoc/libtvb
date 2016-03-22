# copyright 2016 Apache 2 sddekit authors

"""
This module implements functions for generating code based
on parse tree results.

"""


def generate_fn_ptr_field_wrapper_files(path=None, redo=False, filename='fn_ptr_field_wrappers'):
    """
    Generates a header and source file containing regular functions wrapping
    all struct fields which are function pointers.

    _h_template = "{restype} {struct_name}_{field_name}({arg_types});\n"

    _c_template = "{restype} {struct_name}_{field_name}({arg_type_names})\n{{\n\treturn {first_arg}->{field_name}({arg_names});\n}}\n\n"

    data = {
        'restype': fi.restype.typenames + ('*' * fi.restype.ptr),
        'struct_name': self.struct_name[-1],
        'field_name': fi.name,
        'arg_types': ', '.join(arg_types),
        'arg_names': ', '.join(arg_names),
        'arg_type_names': ', '.join('%s %s' % (t, n) for n, t in zip(arg_names, arg_types)),
        'first_arg': arg_names[0],
    }
    self.header_lines.append(self._h_template.format(**data))
    self.source_lines.append(self._c_template.format(**data))


    Parameters
    ----------
    path : string
        Path to write files to.
    filename : string
        Name to give header and source files.

    """
    import api
    path = path or './'
    hpath = join(path, filename + '.h')
    cpath = hpath[:-1] + 'c'
    if exists(hpath) and exists(cpath) and redo is False:
        return
    wrappers = GenFnPtrFieldWrappers.apply(api.header_ast())
    license = ''
    with open('LICENSE', 'r') as fd:
        license = fd.readline().strip()
    with open(hpath, 'w') as fd:
        fd.write('/* {license} */\n\n')
        for line in wrappers.header_lines:
            fd.write(line)
    with open(cpath, 'w') as fd:
        fd.write('''/* copyright 2016 Apache 2 sddekit authors */\n
/* This file was automatically generated based on src/sddekit_simple.h */\n
#include "sddekit.h"\n
''')
        for line in wrappers.source_lines:
            fd.write(line)
