#!/bin/bash

syms=$(nm objs/test_*.o | grep "T test_" | cut -f 3 -d' ')

echo "/* Apache 2.0 INS-AMU 2015 */"
echo

echo "extern int sk_test_report();"
for sym in $syms
do
	echo "extern int $sym();"
done

echo
echo "int main ()"
echo "{"

for sym in $syms
do
	printf "\t$sym();\n"
done

printf "\treturn sk_test_report();\n"
echo "}"
