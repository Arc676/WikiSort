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

void mergeSort(void** array, size_t len, size_t size, COMP_FUNC cmp) {
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

	for (int a = 0, b = 0, i = 0; i < len; i++) {
		if (a >= len1 || (b < len2 && cmp(adv(secondHalf, b * size), adv(firstHalf, a * size)) <= 0)) {
			memcpy(adv(array, i * size), adv(secondHalf, b * size), size);
			b++;
		} else if (b >= len2 || (a < len1 && cmp(adv(firstHalf, a * size), adv(secondHalf, b * size)) <= 0)) {
			memcpy(adv(array, i * size), adv(firstHalf, a * size), size);
			a++;
		}
	}

	free(firstHalf);
	free(secondHalf);
}
