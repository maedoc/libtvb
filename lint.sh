#!/bin/bash

# Apache 2.0 INS-AMU 2015

# find some errors related to sddekit's coding practices

echo "[lint.sh] looking for unchecked mallocs:"
grep -n malloc src/*.c | grep -v SK_MALLOCHECK | nl
