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

// Shellsort gap sequence memoization

// This program aims to determine if memoization reduces
// the runtime of sorting algorithms by a noticeable amount
// by saving on the time required to generate the gap sequence

#include "shell.h"
#include "testprog.h"
int *nums, *copy;

int *shellGaps = 0;
int shellMemoized = 0;

int *prattGaps = 0;
int prattMemoized = 0;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		nums[i] = rand() % BOUND;
	}
	if (shellGaps) {
		free(shellGaps);
		free(prattGaps);
	}
	prattGaps = shellGaps = 0;
	prattMemoized = shellMemoized = 0;
}

unsigned long shellTest(int arrlen, GapSequence seq, int* memoized, int** gaps) {
	memcpy(copy, nums, arrlen * sizeof(int));
	TIME start, end;
	getClock(&start);
	shellSort((void**)copy, arrlen, sizeof(int), cmp_int, seq, memoized, gaps);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long shell(int arrlen) {
	return shellTest(arrlen, Shell_1959, &shellMemoized, &shellGaps);
}

unsigned long pratt(int arrlen) {
	return shellTest(arrlen, A003586, &prattMemoized, &prattGaps);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "memoization test", 4,
		"Shell 1959 No Mem",
		"Shell 1959 Mem",
		"Pratt 3-smooth No Mem",
		"Pratt 3-smooth Mem"
	);
	if (!output) {
		return 1;
	}

	// allocate memory for list
	nums = malloc(MAX_LEN * sizeof(int));
	copy = malloc(MAX_LEN * sizeof(int));

	// allocate memory for storing times
	unsigned long** data = makeData(4);
	TEST_FUNC *tests[4] = {
		shell, shell, pratt, pratt
	};
	runTests(output, generate, tests, 4, data);
	destroyData(data, 4);

	free(shellGaps);
	free(prattGaps);

	free(nums);
	free(copy);

	return 0;
}
