/*
 * Hello world program in OpenMP
 * To compile and run:
 * $ g++ -fopenmp -o hello helloWorld.cpp
 * $ ./hello
 */

#include <omp.h>
#include <stdio.h>

int main () {

	// program executes sequentially at this point
	printf("Hello world outside\n");

	/*
	 * pragma is short for pragmatic information.
	 * It is a preprocessor directive that consists
	 * of useful information on how a compiler
	 * should process the program following it
	 */

	// allow parallel execution of the code in { }
	#pragma omp parallel 
	{
		// get the thread id
		int tid = omp_get_thread_num();
		// get the number of threads
		int numt = omp_get_num_threads();
		// print hello world
		printf("Hello world: %d of %d\n", tid, numt);
	}

	return 0;
}

/*
 * A possible output of this program can be following (num_threads = 4):
 * Hello world outside
 * Hello world 0 of 4
 * Hello world 2 of 4
 * Hello world 3 of 4
 * Hello world 1 of 4
 */