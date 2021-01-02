//Copyright (C) 2019-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

// WikiSort sample program
// Bubble sort, visualized (compile library and this program with the VISUALIZER macro defined)
// Input: the length of the list
// Output: a list of random integers of the given length, before and after sorting, with
//	all pointer advancements and element swaps printed to the console

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "allsorts.h"

VISUALIZER_SWAP* visualizer_itemsSwapped;
VISUALIZER_ADV* visualizer_pointerAdvanced;
VISUALIZER_ABORT_REQ* visualizer_abortRequested;
VISUALIZER_UPDATE* visualizer_updateArray;

int abortReq() {
	return 0;
}

void update(void** arr, int len, int size) {}

void swapped(void** a, void** b) {
	printf("Swapped elements at %p and %p\n", a, b);
}

void advanced(void** ptr, int dist) {
	printf("Advanced ptr to %p by %d\n", ptr, dist);
}

int main(int argc, char* argv[]) {
	visualizer_itemsSwapped = swapped;
	visualizer_pointerAdvanced = advanced;

	// Unused visualizer calls
	visualizer_abortRequested = abortReq;
	visualizer_updateArray = update;

	if (argc != 2) {
		return 1;
	}
	srand(time(NULL));
	int len = atoi(argv[1]);
	int* arr = (int*)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++) {
		arr[i] = rand() % 100;
	}
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	bubbleSort((void**)arr, len, sizeof(int), cmp_int);
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	if (isSorted((void**)arr, len, sizeof(int), cmp_int)) {
		printf("Sorted!\n");
	} else {
		fprintf(stderr, "Failed to sort list.\n");
	}
	free(arr);
	return 1;
}
