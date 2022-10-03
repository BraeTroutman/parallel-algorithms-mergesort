#!/bin/sh
echo "length,bc,mergesort,stl_sort,speedup" > data/problem_three.csv
echo {1..4096} | tr ' ' "\n" | xargs -I{} ./bin/par-merge 10 1000000 {} 8 >> data/problem_three.csv

