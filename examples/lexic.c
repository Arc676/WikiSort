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

// WikiSort sample program
// Lexicographic sort
// Input: a list of words/strings
// Output: the list of points sorted by lexicographic order

#include <stdio.h>
#include <stdlib.h>

#include "radix.h"

int main(int argc, char* argv[]) {
	int len = argc - 1;
	char** arr = malloc(len * sizeof(char*));
	for (int i = 0; i < len; i++) {
		int len = strlen(argv[i + 1]);
		arr[i] = malloc(len);
		memcpy(arr[i], argv[i + 1], len);
	}
	for (int i = 0; i < len; i++) {
		printf("%s ", arr[i]);
	}
	printf("\n");
	radixSortMSDRec((void**)arr, len, sizeof(char*), cmp_strlen, 26, str_base_cmp_MSD, str_base_MSD, 'a', 0);
	for (int i = 0; i < len; i++) {
		printf("%s ", arr[i]);
	}
	printf("\n");
	if (isSorted((void**)arr, len, sizeof(char*), cmp_str)) {
		printf("List sorted!\n");
		return 0;
	}
	fprintf(stderr, "Failed to sort list\n");
	return 1;
}
