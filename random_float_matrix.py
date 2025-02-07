#!/usr/bin/env python
# -*- coding: utf-8 -*-

# this small helper script generates test matrices of the given dimension and
# outputs them to stdout so that you can pipe it into files. The elements are
# separated by '\t'.
#
# Synopsis:
#   ./gen_matrices.py 4 4
#
# Author: Philipp Böhm

import sys
import random

try:
    dim_x, dim_y = int(sys.argv[1]), int(sys.argv[2])
except:
    sys.stderr.write("error parsing matrix dimensions ...\n")
    raise


for row in range(0, dim_x):
    delim = "\t"
    x = [random.uniform(0, 9999) for x in range(0, dim_y) ]
    print(delim.join(map(str, x)))
