//Copyright (C) 2018  Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

// *******

// Integer vs Float comparison test

// This program generates two random lists, one of which contains integers
// while the other contains doubles. Then the lists are sorted using Shellsort
// with 3-smooth numbers as the gap sequence. The lists contain pseudorandomly
// generated values between 0 and RAND_MAX/100. The integral portion of the
// elements are equal. Only the non-integral portions of the elements differ,
// as integers have none.

// Data is outputted to a file with name set to the first argument.

// You can define the following macros during compilation to customize the test

// Maximum array length
#ifndef MAX_LEN
#define MAX_LEN 600
#endif

// Starting array length
#ifndef START_LEN
#define START_LEN 100
#endif

// Array length increment
#ifndef LEN_INC
#define LEN_INC 100
#endif

// 1 for linear growth (add LEN_INC), 0 for exponential growth (multiply by LEN_INC)
// defaults to exponential
#ifndef LIN_GROWTH
#define LIN_GROWTH 0
#endif

// Number of trials to perform for each array length
#ifndef MAX_TRIALS
#define MAX_TRIALS 10
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shell.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: id output.csv\n");
		return 1;
	}
	srand(time(NULL));
	FILE* output = fopen(argv[1], "w");
	if (!output) {
		fprintf(stderr, "Failed to open output file\n");
		return 1;
	}
	fprintf(output, "Length,");
	for (int i = 0; i < MAX_TRIALS; i++) {
		fprintf(output, "Ints %d,", i + 1);
	}
	fprintf(output, "Ints AVG,");
	for (int i = 0; i < MAX_TRIALS; i++) {
		fprintf(output, "Doubles %d,", i + 1);
	}
	fprintf(output, "Doubles AVG\n");

	// allocate memory for lists
	int* ints = malloc(MAX_LEN * sizeof(int));
	double* doubles = malloc(MAX_LEN * sizeof(double));

	unsigned long data[2][MAX_TRIALS];

	for (int arrlen = START_LEN; arrlen <= MAX_LEN;) {
		// generate random data
		for (int i = 0; i < arrlen; i++) {
			doubles[i] = (double)rand() / 100;
			ints[i] = (int)doubles[i];
		}
		printf("\r\tSorting arrays of length %d...", arrlen);
		fflush(stdout);
		fprintf(output, "%d,", arrlen);

		for (int trial = 0; trial < MAX_TRIALS; trial++) {
			clock_t start, end;

			start = clock();
			shellSort((void**)ints, arrlen, sizeof(int), cmp_int, A003586);
			end = clock();
			data[0][trial] = end - start;

			start = clock();
			shellSort((void**)doubles, arrlen, sizeof(double), cmp_double, A003586);
			end = clock();
			data[1][trial] = end - start;
		}
		for (int sort = 0; sort < 2; sort++) {
			long double total = 0;
			for (int trial = 0; trial < MAX_TRIALS; trial++) {
				total += data[sort][trial];
				fprintf(output, "%lu,", data[sort][trial]);
			}
			fprintf(output, "%Lf,", total / MAX_TRIALS);
		}
		fprintf(output, "\n");
		if (LIN_GROWTH) {
			arrlen += LEN_INC;
		} else {
			arrlen *= LEN_INC;
		}
	}
	printf("\nProgram terminated\n");
	fclose(output);
	return 0;
}
