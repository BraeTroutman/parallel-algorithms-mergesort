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

2. Parallelize the code correctly

3. Explore the performance of your parallel code

4. Analyze the task scheduling problem

5. Evaluate your parallel performance

