echo "n,bc,num_threads,mergesort_time,stl_sort_time,speedup" > data/problem_three.csv
for ((i=1; i<=100; i+=2))
do
	./bin/par-merge 10 1000000 $i 8 >> data/problem_three.csv
	echo base case of size $i
done	
for ((i=100; i<=500000; i+=100))
do
	./bin/par-merge 10 1000000 $i 8 >> data/problem_three.csv
	echo base case of size $i
done	

