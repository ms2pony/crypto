#!/usr/bin/bash
make # test_mul_avx2_2()
./app > log.txt
python3 test_mul_avx2.py