#!/bin/bash

# Apache 2.0 INS-AMU 2015

syms=$(nm objs/test_*.o | grep "T test_" | cut -f 3 -d' ')

echo "/* Apache 2.0 INS-AMU 2015 */"
echo "#include <string.h>"
echo "#include <stdio.h>"

echo "void print_usage() {"
echo "  printf(\"sk_tests --all --test_foo --test_bar .. where test suites are\\n\");"
for sym in $syms
do
	echo "  printf(\"\t--$sym\n\");"
done
echo "}"

echo "extern int sk_test_report();"
for sym in $syms
do
	echo "extern int $sym();"
done

echo "int all() {"
for sym in $syms
do
	printf "\t$sym();\n"
done
echo "  return 0;"
echo "}"

echo
echo "int main (int argc, char **argv)"
echo "{"
echo "int i;"
echo "if (argc==1) print_usage(); else "
echo "for (i=1; i<argc; i++) {"
echo "if (!strcmp(\"--all\", argv[i])) all();"
for sym in $syms
do
	printf "if (!strcmp(\"--$sym\", argv[i])) $sym();\n"
done
echo "}"

printf "\treturn sk_test_report();\n"
echo "}"
