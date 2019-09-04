/*
 * Matrix multiplication in parallel using OpenMP
 */

#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <random>
using namespace std;

#define M 1000
#define N 1000
#define P 1000

int a[M][N];
int b[N][P];
int c[M][P];

// function to print a matrix with 1000 columns
void printMatrix(int mat[][1000], int r, int c) {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main () {

	// initialize the matrices a and b with random values
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> distribution(0, 1000);
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			a[i][j] = distribution(generator);
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < P; ++j) {
			b[i][j] = distribution(generator);
		}
	}
	
	double t1, t2;
	printf("Time for matrix multiplication of two %dx%d matrices using different no. of threads:\n", M, N);
	
	for (int num_threads = 1; num_threads <= 10; ++num_threads) {
		// set the number of threads to num_threads
		omp_set_num_threads(num_threads);
		memset(c, sizeof(c), 0);
		// time before starting matrix multiplication
		t1 = omp_get_wtime();
		// reduction is used because adding the values to c[i][j] should be done with barrier
		#pragma omp parallel reduction(+: c)
		{
			// collapse 3 is used since all the three loops work will be divided amongst threads
			#pragma omp for collapse(3)
			for (int i = 0; i < M; ++i) {
				for (int j = 0; j < P; ++j) {
					for (int k = 0; k < N; ++k) {
						c[i][j] += (a[i][k] * b[k][j]);
					}
				}
			}
		}
		// time after finishing matrix multiplication
		t2 = omp_get_wtime();
		printf("Using %d thread(s): %g\n", num_threads, t2 - t1);
	}

	return 0;
}