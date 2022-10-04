echo "n,bc,num_threads,mergesort_time,stl_sort_time,speedup,efficiency" > data/problem_five.csv
for ((i=1; i<=44; i++))
do
	./bin/par-merge 10 $((2**24)) $(((2**24)/i)) $i n >> data/problem_five.csv
	echo base case of size $(((2**24)/i))
done	

