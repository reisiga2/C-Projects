/*
 * hwOneMain.c
 *
 *  Created on: Sep 3, 2014
 *      Author: Mostafa
 */
# include <stdio.h>
# include <stdlib.h>
# include <time.h>


const int min = 100; // min size of matrix in benchmark
const int max = 1000; // max size of matrix in benchmark
int indicator; // indicate what part of problem you want to run

int main(void) {

	int matrix_fill_random(int n1, int n2, double *a);
	int matrix_multiply(int n1, int n2, int n3, double *a, double *b, double *c);
	int matrix_print(int n1, int n2, double *a);
	int matrixTest(void);
	float matrixBenchmark(int n, int numIteration);

	float aveTime[max - min]; //array of average time of matrix multiplication

	printf("enter 1 to run matrix test or enter 2 to run matrix benchmark: \n");
	scanf("%d", &indicator);
	if (indicator == 1) {
	   matrixTest(); // test the matrix multiplication
	} else {
        int i;
        for (i = min; i < max; i++) {
            aveTime[i - min] = matrixBenchmark(i, 100);
        printf("%.20f \n", aveTime[i - min]);
	    }
	}
    return 0;
}
/*
* this function fills a matrix with random numbers
*@param n1, n2, a
*@retun 0
*/
int matrix_fill_random(int n1, int n2, double *a) {
	double *p = a;
	for(p = a; p < a + n1*n2; p++) {
		*p = - 10 + 20 * ((double)rand()/(double)RAND_MAX);
	}
    return 0;
}

/*
* this function multiply a matrix of size n1*n2 with a matrix of size n2*n3
*@param n1, n2, n3, a, b, c
*@return 0
*/
int matrix_multiply(int n1, int n2, int n3, double *a, double *b, double *c) {
    int i, j, k;
    for (i = 0; i < n1; i++) {
		for(j = 0; j < n3; j++) {
			c[n3 * i + j]=0;
			for (k = 0; k < n2; k++) {
				c[n3 * i + j] += a[n2 * i + k] * b[n3 * k + j];
		    }
		}
	}
    return 0;
}
/* this function prints a matrix
* @param n1, n2, a
* @ return 0
*/
int matrix_print(int n1, int n2, double *a) {
	double *p = a;
	int i;
	for (i = 0; i < n1; i++) {
	    for(p = a + i * n2; p < a + (i + 1) * n2; p++) {
             printf("%10f  ", *p);
	    }
	 printf("\n");
	}
    return 0;
}

/* This function tests all other function by generating,
* multiplying and printing them
* @ param n1, n2, n3, a, b, c
* @ return 0
*/
int matrixTest(void) {
    const int n1 = 4;
    const int n2 = 3;
    const int n3 = 2;
    double a[n1][n2];
    double b[n2][n3];
    double c[n1][n3];
    matrix_fill_random(n1, n2, (double *)a);
    matrix_fill_random(n2, n3, (double *)b);
    matrix_multiply(n1, n2, n3, (double *)a, (double *)b, (double *)c);
    matrix_print(n1, n2, (double *) a);
    printf("\n");
    matrix_print(n2, n3, (double *) b);
    printf("\n");
    matrix_print(n1, n3, (double *) c);
    return 0;
}

/* This function multiply square matrices several times
* and finds the average time it take.
* @ param n, numIteration
* @ return multiplication time
*/
float matrixBenchmark(int n, int numIteration) {
    clock_t t1, t2;
    int i = 0;
    double a[n][n];
    double b[n][n];
    double c[n][n];
    
    matrix_fill_random(n, n, (double *) a);
    matrix_fill_random(n, n, (double *) b);
    
    t1 = clock();
    for (i = 0; i < numIteration; i++) {
    	matrix_multiply(n, n, n, (double *) a, (double *) b, (double *) c);
    }
    t2 = clock();
    
	float totalTimeInSec = (float) (t2 - t1) / (float)CLOCKS_PER_SEC;
	float averageTime = totalTimeInSec/ (float) numIteration;
    return averageTime;
}
