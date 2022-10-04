#include <iostream>
#include <algorithm>
#include <climits>
#include <cassert>
#include <omp.h>
#include <string>
#include <sstream>

using namespace std;

void mergesort(int* a, int* tmp, int n, int bc);
void medianofunion(int* a, int n, int& ia, int* b, int m, int& ib);
void recmerge(int* a, int n, int* b, int m, int* c, int bc);
string printArray(int* arr, int len);
void parcopy(int* start, int* end, int* dest, int bc);

char verbose;

int main(int argc, char** argv) {

    // read inputs
    if(argc != 6) {
        cout << "Usage: ./a.out seed length basecase nthreads verbose(y/n)" << endl;
        return 1;
    }
    srand(atoi(argv[1]));
    int length = atoi(argv[2]);
    int bc = atoi(argv[3]);
    int nthreads = atoi(argv[4]);
	verbose = argv[5][0];	
    omp_set_num_threads(nthreads);

    // allocate memory
    int* v = new int[length]; // array to be sorted
    int* t = new int[length]; // temporary workspace
    int* v2 = new int[length]; // copy for checking

    // initialize input randomly
    for (int i = 0; i < length; i++) {
        v[i] = v2[i] = rand() % length;
    }

    // sort array using mergesort (and time it)
    double start_mergeSort = omp_get_wtime();
    #pragma omp parallel
    #pragma omp single
    mergesort(v, t, length, bc);
    double elapsed_mergeSort = omp_get_wtime() - start_mergeSort;

    // sort array using STL (and time it)
    double start_sort = omp_get_wtime();
    sort(v2,v2+length);
    double elapsed_sort = omp_get_wtime() - start_sort;

    // check outputs, make sure they match
    for(int i = 0; i < length; i++) {
        assert(v[i] == v2[i]);
    }

    // report timings
    cout << length << ',' << bc << ',' << nthreads << ',' <<
	    elapsed_mergeSort << ',' << elapsed_sort << ',' << 
	    elapsed_sort / elapsed_mergeSort << ',' <<
		(elapsed_sort / elapsed_mergeSort) / (double) nthreads << endl; 

    delete [] v2;
    delete [] t;
    delete [] v;

}

// sorts array a of length n, tmp is workspace of length n,
// bc is base case size to switch to STL sort
void mergesort(int* a, int* tmp, int n, int bc)
{
    int tid = omp_get_thread_num();
//    cout << "Thread #" << tid << " is sorting: ";
//    printArray(a, n);

    if(n <= bc) {
		if (verbose == 'y') {
			#pragma omp critical
			cout << "Thread #" << tid << 
				" is executing a mergeSORT base case on the list: " << 
				printArray(a,n) << endl;
		}
        sort(a, a+n);
        return;
    }
    
    // sort left and right recursively
    int mid = n / 2; 
    #pragma omp task
    mergesort(a, tmp, mid, bc);
    mergesort(a + mid, tmp + mid, n - mid, bc);
    #pragma omp taskwait
    // merge left and right into tmp and copy back into a (using STL)
    recmerge(a, mid, a+mid, n-mid, tmp, bc);
    parcopy(tmp,tmp+n,a,bc);
}

// merges sorted arrays a (length n) and b (length m) into array c (length n+m),
// bc is base case size to switch to STL merge
void recmerge(int* a, int n, int* b, int m, int* c, int bc) {
    if(n+m<=bc){
		int tid = omp_get_thread_num();
		if (verbose == 'y') {
			#pragma omp critical
			cout << "Thread #" << tid << 
				" is executing a MERGE base case on the lists:" << 
				printArray(a,n) << " " << 
				printArray(b,m) << endl;
		}
        merge(a, a+n, b, b+m, c);
        return;
    }

    // compute median of union with i elements of a and j elements of b <= median
    int i, j;
    medianofunion(a, n, i, b, m, j);

    // merge left and right recursively
    #pragma omp task 
    recmerge(a, i, b, j, c, bc);
    recmerge(a+i, n-i, b+j, m-j, c+i+j, bc);
    #pragma omp taskwait
}
    
// computes median of union of array a of length n and array b of length m
// assuming elements of a and b are already internally sorted; upon return:
// ma is number of elements in a less than or equal to median of union,
// mb is number of elements in b less than or equal to median of union
void medianofunion(int *a, int n, int& ma, int *b, int m, int& mb) 
{
    // enforce that a is smaller of two arrays
    if(n > m) {
        medianofunion(b,m,mb,a,n,ma);
        return;
    }

    // run binary search in array a
    int i = 0;
    int j = n;
    while (i <= j) {
        // get middle two elements of each array (use extremes to handle corner cases)
        ma = (i + j) / 2;
        mb = (n + m + 1) / 2 - ma;
        int la = (ma > 0) ? a[ma - 1]: INT_MIN; 
        int lb = (mb > 0) ? b[mb - 1] : INT_MIN;
        int ra = (ma < n) ? a[ma] : INT_MAX;
        int rb = (mb < m) ? b[mb] : INT_MAX;

        // check for complete (la <= {ra,rb} and lb <= {ra,rb})
        if (la <= rb && lb <= ra)
            return;

        // continue search
        if (la > rb) 
            j = ma - 1;
        else // lb > ra
            i = ma + 1;
    }
}

string printArray(int* a, int len) {
	ostringstream str;
	str << "[ ";
	for (int i = 0; i < len; i++) {
		str << a[i] << " ";
	}
	return str.str() + "]";
}

void parcopy(int* start, int* end, int* dest, int bc) {
	int len = end - start;
	if (len <= bc) {
		copy(start, end, dest);
		return;
	}

	int mid = len/2;
	#pragma omp task
	parcopy(start, start+mid, dest, bc); 
	parcopy(start+mid, end, dest+mid, bc);
	#pragma omp taskwait
}	

