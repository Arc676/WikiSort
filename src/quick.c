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

#include "quick.h"

void quickSort(void** array, size_t len, size_t size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	int pivot = len/2;
	int less = 0, equal = 1, more = 0;

	void** smaller = malloc(len * size);
	void** same = malloc(len * size);
	void** greater = malloc(len * size);

	void** pivotElement = adv(array, pivot * size);
	memcpy(same, pivotElement, size);

	// move elements into new lists
	for (int i = 0; i < len; i++) {
		if (i == pivot) {
			continue;
		}
		void** element = adv(array, i * size);
		int res = cmp(element, pivotElement);
		switch (res) {
		case -1:
			memcpy(adv(smaller, less++ * size), element, size);
			break;
		case 0:
			memcpy(adv(same, equal++ * size), element, size);
			break;
		case 1:
		default:
			memcpy(adv(greater, more++ * size), element, size);
			break;
		}
	}

	// sort partitions
	quickSort(smaller, less, size, cmp);
	quickSort(greater, more, size, cmp);

	// move sorted partitions back into original list
	uint64_t index = (uint64_t)array;

	memcpy((void**)index, smaller, less * size);
	index += less * size;

	memcpy((void**)index, same, equal * size);
	index += equal * size;

	memcpy((void**)index, greater, more * size);
}
