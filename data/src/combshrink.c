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

// Comb sort shrink factor comparison

// The comb sort algorithm improves on bubble sort and uses a similar approach
// to Shellsort. In fact, the gap sequence described by Shell in 1959 is
// mathematically similar to what comb sort uses. The shrink factor in Shell's
// gap sequence was 2, but the ideal factor for comb sort was suggested to be
// 1.3 by the original author. This program tests different shrink factors to
// see how they compare.

#include "comb.h"
#include "testprog.h"

int *nums, *copy;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		nums[i] = rand() % BOUND;
	}
}

unsigned long combTest(int arrlen, float shrink) {
	memcpy(copy, nums, arrlen * sizeof(int));
	clock_t start = clock();
	combSort((void**)copy, arrlen, sizeof(int), cmp_int, shrink);
	clock_t end = clock();
	return end - start;
}

unsigned long g0(int arrlen) {
	return combTest(arrlen, 1.1);
}

unsigned long g1(int arrlen) {
	return combTest(arrlen, 1.2);
}

unsigned long g2(int arrlen) {
	return combTest(arrlen, 1.3);
}

unsigned long g3(int arrlen) {
	return combTest(arrlen, 1.4);
}

unsigned long g4(int arrlen) {
	return combTest(arrlen, 1.5);
}

unsigned long g5(int arrlen) {
	return combTest(arrlen, 1.6);
}

unsigned long g6(int arrlen) {
	return combTest(arrlen, 1.7);
}

unsigned long g7(int arrlen) {
	return combTest(arrlen, 1.8);
}

unsigned long g8(int arrlen) {
	return combTest(arrlen, 1.9);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "gaps", 9,
		"1.1", "1.2", "1.3", "1.4", "1.5", "1.6", "1.7", "1.8", "1.9"
	);
	if (!output) {
		return 1;
	}

	// allocate memory for list
	nums = malloc(MAX_LEN * sizeof(int));
	copy = malloc(MAX_LEN * sizeof(int));

	// allocate memory for storing times
	unsigned long** data = makeData(9);
	TEST_FUNC *tests[9] = {
		g0, g1, g2, g3, g4, g5, g6, g7, g8
	};
	runTests(output, generate, tests, 9, data);
	destroyData(data, 9);

	return 0;
}
