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

// Shellsort gap sequence comparison

// Different gap sequences have been shown to result in different
// time complexities for the Shellsort algorithm. This program aims to
// test the different gap sequences to determine their relative efficiencies.

#include "shell.h"
#include "testprog.h"

int *nums, *copy;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		nums[i] = rand() % BOUND;
	}
}

unsigned long shellTest(int arrlen, GapSequence seq) {
	memcpy(copy, nums, arrlen * sizeof(int));
	clock_t start = clock();
	shellSort((void**)copy, arrlen, sizeof(int), cmp_int, seq);
	clock_t end = clock();
	return end - start;
}

unsigned long g0(int arrlen) {
	return shellTest(arrlen, (GapSequence)0);
}

unsigned long g1(int arrlen) {
	return shellTest(arrlen, (GapSequence)1);
}

unsigned long g2(int arrlen) {
	return shellTest(arrlen, (GapSequence)2);
}

unsigned long g3(int arrlen) {
	return shellTest(arrlen, (GapSequence)3);
}

unsigned long g4(int arrlen) {
	return shellTest(arrlen, (GapSequence)4);
}

unsigned long g5(int arrlen) {
	return shellTest(arrlen, (GapSequence)5);
}

unsigned long g6(int arrlen) {
	return shellTest(arrlen, (GapSequence)6);
}

unsigned long g7(int arrlen) {
	return shellTest(arrlen, (GapSequence)7);
}

unsigned long g8(int arrlen) {
	return shellTest(arrlen, (GapSequence)8);
}

unsigned long g9(int arrlen) {
	return shellTest(arrlen, (GapSequence)9);
}

unsigned long g10(int arrlen) {
	return shellTest(arrlen, (GapSequence)10);
}

unsigned long g11(int arrlen) {
	return shellTest(arrlen, (GapSequence)11);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "gaps", GAP_COUNT,
		"Shell 1959",
		"Frank & Lazarus 1960",
		"Hibbard 1963",
		"Papernov & Stasevich 1965",
		"Pratt 1971 (3-smooth)",
		"Pratt 1971 (3^k - 1)/2",
		"Incerpi & Sedgewick 1985",
		"Sedgewick 1986 (single formula)",
		"Sedgewick 1986 (odd/evens)",
		"Gonnet & Baeza-Yates 1991",
		"Tokuda 1992",
		"Ciura 2001"
	);
	if (!output) {
		return 1;
	}

	// allocate memory for list
	nums = malloc(MAX_LEN * sizeof(int));
	copy = malloc(MAX_LEN * sizeof(int));

	// allocate memory for storing times
	unsigned long** data = makeData(GAP_COUNT);
	TEST_FUNC *tests[GAP_COUNT] = {
		g0, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11
	};
	runTests(output, generate, tests, GAP_COUNT, data);
	destroyData(data, GAP_COUNT);

	return 0;
}
