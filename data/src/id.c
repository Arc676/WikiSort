//Copyright (C) 2018-9 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

// *******

// Integer vs Float comparison test

// This program generates two random lists, one of which contains integers
// while the other contains doubles. Then the lists are sorted using Shellsort
// with the value of the GAP macro as the gap sequence. The lists contain
// generated values between 0 and RAND_MAX/100. The integral portion of the
// elements are equal. Only the non-integral portions of the elements differ,
// as integers have none.

// The following macro can be set during compilation to change the
// gap sequence to be used. Defaults to the single formula sequence
// described by Sedgewick in 1986.

#ifndef SEQ
#define SEQ 7
#endif

#include "shell.h"
#include "testprog.h"

int* ints;
double* doubles;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		doubles[i] = (double)rand() / 100;
		ints[i] = (int)doubles[i];
	}
}

unsigned long testInts(int arrlen) {
	TIME start, end;
	getClock(&start);
	shellSort((void**)ints, arrlen, sizeof(int), cmp_int, (GapSequence)SEQ, 0, 0);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long testDoubles(int arrlen) {
	TIME start, end;
	getClock(&start);
	shellSort((void**)doubles, arrlen, sizeof(double), cmp_double, (GapSequence)SEQ, 0, 0);
	getClock(&end);
	return getDelta(&start, &end);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "id", 2, "Ints", "Doubles");
	if (!output) {
		return 1;
	}

	// allocate memory for lists
	ints = malloc(MAX_LEN * sizeof(int));
	doubles = malloc(MAX_LEN * sizeof(double));

	unsigned long** data = makeData(2);
	TEST_FUNC *tests[2] = {
		testInts,
		testDoubles
	};
	runTests(output, generate, tests, 2, data);
	destroyData(data, 2);

	free(ints);
	free(doubles);

	return 0;
}
