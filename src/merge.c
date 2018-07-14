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

#include "merge.h"

void mergeSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len == 1) {
		return;
	}

	int len1 = len / 2;
	int len2 = len - len1;

	void** firstHalf = malloc(len1 * size);
	void** secondHalf = malloc(len2 * size);

	memcpy(firstHalf, array, len1 * size);
	memcpy(secondHalf, adv(array, len1 * size), len2 * size);

	mergeSort(firstHalf, len1, size, cmp);
	mergeSort(secondHalf, len2, size, cmp);

	mergeArrays(
		array, len,
		firstHalf, len1,
		secondHalf, len2,
		size, cmp
	);

	free(firstHalf);
	free(secondHalf);
}

void mergeArrays(void** dst, int len, void** arr1, int len1, void** arr2, int len2, int size, COMP_FUNC cmp) {
	for (int a = 0, b = 0, i = 0; i < len; i++) {
		void** A = adv(arr1, a * size);
		void** B = adv(arr2, b * size);
		if (a >= len1 || (b < len2 && cmp(B, A) <= 0)) {
			memcpy(adv(dst, i * size), B, size);
			b++;
		} else if (b >= len2 || (a < len1 && cmp(A, B) <= 0)) {
			memcpy(adv(dst, i * size), A, size);
			a++;
		}
	}
}
