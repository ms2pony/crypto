#!/usr/bin/bash
make
./app > log.txt
python3 test_mul_avx2.py