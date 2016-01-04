# copyright 2016 Apache 2 sddekit authors

import os
import glob

here = os.path.abspath(os.path.dirname(__file__))

def get_test_name(line):
	topic, name = line.split('(')[1].split(')')[0].split(',')
	test_name = 'sd_test__%s_%s' % (topic.strip(), name.strip())
	return test_name

def test_files():
	test_files = glob.glob(os.path.join(here, 'test_*.c'))
	for file_name in test_files:
		yield file_name

def file_test_def_lines(file_name):
	with open(file_name, 'r') as fd:
		for line in fd.readlines():
			if 'TEST' in line:
				yield line

all_source = """/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

{decls}

int sd_test_run_all() {{
{calls}
	return sd_test_report();
}}
"""

if __name__ == '__main__':

	import sys

	tests = []
	for file_name in test_files():
		for test_line in file_test_def_lines(file_name):
			tests.append(get_test_name(test_line))
	
	decls = "\n".join("int " + name + "();" for name in tests)
	calls = "\n".join("\t" + name + "();" for name in tests)


	if len(sys.argv) > 1 and sys.argv[1] == '--to-cwd':
		out_fname = "test_all.c"
	else:
		out_fname = os.path.join(here, "test_all.c")

	with open(out_fname, "w") as fd:
		fd.write(all_source.format(decls=decls, calls=calls))


