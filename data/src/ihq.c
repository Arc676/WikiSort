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

// ********

// Introsort/Heapsort/Quicksort test

// An introsort algorithm employs quicksort techniques until a certain
// number of iterations has been reached before switching to heapsort.
// This program generates random lists of increasing lengths and runs
// all three sorting algorithms on identical lists to compare their runtime.

#include "intro.h"
#include "testprog.h"

int *nums, *copy;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		nums[i] = rand() % BOUND;
	}
}

unsigned long introTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	introSort((void**)copy, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);;
}

unsigned long heapTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	heapSort((void**)copy, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);;
}

unsigned long quickTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	quickSort((void**)copy, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);;
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "ihq", 3, "Introsort", "Heapsort", "Quicksort");
	if (!output) {
		return 1;
	}

	// allocate memory for list
	nums = malloc(MAX_LEN * sizeof(int));
	copy = malloc(MAX_LEN * sizeof(int));

	// allocate memory for storing times
	unsigned long** data = makeData(3);
	TEST_FUNC *tests[3] = {
		introTest,
		heapTest,
		quickTest
	};
	runTests(output, generate, tests, 3, data);
	destroyData(data, 3);

	return 0;
}
