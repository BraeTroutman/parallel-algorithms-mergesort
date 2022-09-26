# CSC 726 Homework 3: OpenMP Mergesort

We will be parallelizing mergesort using the algorithm we analyzed in class. We’ll be sorting ints that
are initialized randomly from a uniform distribution, but don’t exploit those facts in your implementation
(your algorithm should be generalizable to sorting other types and distributions). For notation, let’s let n
be the length of the array (length in the code) and p be the number of threads (nthreads in the code).
Instead of recursing down to subarrays of size 1, we will use a base case size b (bc in the code) below which
we’ll resort to the C++ STL’s sort function. Likewise, we’ll use the same base case size for the recursive
merge function, where we’ll use STL’s merge function.

## Questions:

1. Define $k$ to be the number of  levels of the mergesort recursion tree (assume that $\frac{n}{b}$ is a power of 2)
	1. how many mergesort base cases are there as a function of $k$
	2. how many merge base cases are there as a function of $k$

2. Parallelize the code correctly
	1. parallelize  the mergesort and merge functions  using OpenMP's `task` and `taskwait` constructs.
	2. write a recursive parallel function to replace the call to STL's `copy` function, and use the same base case size as `mergesort` and `merge`

3. Explore the performance of your parallel code
	1. what effect does $bc$ have on the performance of your parallel code? What is the best strategy for choosing $bc$ given $n$ and $p$? Justify your choice with empirical evidence.
	2. explain the performance behavior you see as you vary $bc$

4. Analyze the task scheduling problem
	1. what mergesort base cases can be performed in parallel? What merge base cases can be executed in parallel?
	2. if you could decide on a static schedule of base cases to threads, what would it be?
	3. instrument your code to determine how OpenMP schedules tasks to threads (it will likely vary from execution to execution). How does it compare to your preferred static schedule? What makes your static schedule better (or worse)?

5. Evaluate your parallel performance
	1. report your parallel performance (speedup and efficiency) for a significantly large problem from 1 to 44 threads. Always compare to the sequential performance of STL's `sort` function. 
	2. why does efficiency differ between $p$ being a power of 2 or not?
	3. what are the barriers to better parallel scaling?

