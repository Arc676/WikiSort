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

// This program aims to compare the runtime of the GENERATION of the gap
// sequences used for shellsort. As some of the sequences are described by more
// complicated mathematics, it's possible that some will be harder to generate
// than others.


#include "shell.h"
#include "testprog.h"

void generate(int arrlen) {
}

unsigned long gapTest(int arrlen, int seq) {
	clock_t start = clock();
	int count;
	int* gaps = gapSeqs[seq](arrlen, &count);
	free(gaps);
	clock_t end = clock();
	return end - start;
}

unsigned long g0(int arrlen) {
	return gapTest(arrlen, 0);
}

unsigned long g1(int arrlen) {
	return gapTest(arrlen, 1);
}

unsigned long g2(int arrlen) {
	return gapTest(arrlen, 2);
}

unsigned long g3(int arrlen) {
	return gapTest(arrlen, 3);
}

unsigned long g4(int arrlen) {
	return gapTest(arrlen, 4);
}

unsigned long g5(int arrlen) {
	return gapTest(arrlen, 5);
}

unsigned long g6(int arrlen) {
	return gapTest(arrlen, 6);
}

unsigned long g7(int arrlen) {
	return gapTest(arrlen, 7);
}

unsigned long g8(int arrlen) {
	return gapTest(arrlen, 8);
}

unsigned long g9(int arrlen) {
	return gapTest(arrlen, 9);
}

unsigned long g10(int arrlen) {
	return gapTest(arrlen, 10);
}

unsigned long g11(int arrlen) {
	return gapTest(arrlen, 11);
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

	// allocate memory for storing times
	unsigned long** data = makeData(GAP_COUNT);
	TEST_FUNC *tests[GAP_COUNT] = {
		g0, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11
	};
	runTests(output, generate, tests, GAP_COUNT, data);
	destroyData(data, GAP_COUNT);

	return 0;
}
