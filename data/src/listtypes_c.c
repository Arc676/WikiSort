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

// List type comparison (cocktail sort)

// This program generates lists that fit one of the following descriptions
// and then employs a cocktail sort.

// Random:
//	PseudorandomGen number generation provides the values
// Few unique elements:
//	The first len/10 values from the randomGen list are copied to a new list and repeated. Then the list is shuffled.
// Reverse order:
//	Merge sort a copy of the randomGen list and reverse it
// Sort of sorted
//	Run the quicksort partitioning algorithm three times on a copy of the randomGen list

#include "cocktail.h"
#include "tim.h"
#include "bogo.h"
#include "quick.h"
#include "testprog.h"

int *randomGen, *fewunique, *reversed, *kindasorted;

void generate(int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		randomGen[i] = rand() % BOUND;
		fewunique[i] = randomGen[i / 10];
	}
	fisherYates((void**)fewunique, arrlen, sizeof(int));

	memcpy(kindasorted, randomGen, arrlen * sizeof(int));
	int equals;
	int pivot = partition((void**)kindasorted, arrlen, sizeof(int), cmp_int, &equals);
	partition((void**)kindasorted, pivot, sizeof(int), cmp_int, &equals);
	partition((void**)(kindasorted + pivot + equals), arrlen - pivot - equals, sizeof(int), cmp_int, &equals);
}

unsigned long testRandom(int arrlen) {
	TIME start, end;
	getClock(&start);
	cocktailSort((void**)randomGen, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long testReversed(int arrlen) {
	memcpy(reversed, randomGen, arrlen * sizeof(int));
	reverse((void**)reversed, arrlen, sizeof(int));
	TIME start, end;
	getClock(&start);
	cocktailSort((void**)reversed, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long testFewUnique(int arrlen) {
	TIME start, end;
	getClock(&start);
	cocktailSort((void**)fewunique, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

unsigned long testKindaSorted(int arrlen) {
	TIME start, end;
	getClock(&start);
	cocktailSort((void**)kindasorted, arrlen, sizeof(int), cmp_int);
	getClock(&end);
	return getDelta(&start, &end);
}

int main(int argc, char* argv[]) {
	FILE* output = initialize(argc, argv, "lt", 4,
		"Random",
		"Reversed",
		"Few Unique",
		"Kinda sorted");
	if (!output) {
		return 1;
	}

	// allocate memory for lists
	randomGen = malloc(MAX_LEN * sizeof(int));
	fewunique = malloc(MAX_LEN * sizeof(int));
	reversed = malloc(MAX_LEN * sizeof(int));
	kindasorted = malloc(MAX_LEN * sizeof(int));

	unsigned long** data = makeData(4);
	TEST_FUNC *tests[4] = {
		testRandom, testReversed, testFewUnique, testKindaSorted
	};
	runTests(output, generate, tests, 4, data);
	destroyData(data, 4);

	free(randomGen);
	free(fewunique);
	free(reversed);
	free(kindasorted);

	return 0;
}
