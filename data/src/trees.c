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

// ********

// Binary tree sort test

// This program compares the runtime of Cartesian tree sort, Splaysort,
// and the standard treesort. These are all sorting algorithms that
// construct a binary tree and use its properties to sort their inputs.

#include "splay.h"
#include "cartesian.h"
#include "testprog.h"

int *nums, *copy;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		nums[i] = rand() % BOUND;
	}
}

unsigned long cartesianTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	cartesianTreeSort((void**)copy, arrlen, sizeof(int), cmp_int, binTree_cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long treeTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	treeSort((void**)copy, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long splayTest(int arrlen) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	splaySort((void**)copy, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "trees", 3, "Treesort", "Cartesian Tree Sort", "Splaysort");
	if (!output) {
		return 1;
	}

	// allocate memory for list
	nums = malloc(MAX_LEN * sizeof(int));
	copy = malloc(MAX_LEN * sizeof(int));

	// allocate memory for storing times
	unsigned long** data = makeData(3);
	TEST_FUNC *tests[3] = {
		treeTest,
		cartesianTest,
		splayTest
	};
	runTests(output, generate, tests, 3, data);
	destroyData(data, 3);

	free(nums);
	free(copy);

	return 0;
}
