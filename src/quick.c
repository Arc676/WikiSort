//Copyright (C) 2018-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "quick.h"

void quickSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}

	// partition the array
	int equals;
	int pivot = partition(array, len, size, cmp, &equals);

	#ifdef VISUALIZER
	visualizer_updateArray(array, len, size);

	if (visualizer_abortRequested()) {
		return;
	}
	#endif

	// sort the elements smaller than the pivot
	quickSort(array, pivot, size, cmp);

	// sort the elements larger than the pivot
	void** greater = adv(array, (pivot + equals) * size);
	quickSort(greater, len - pivot - equals, size, cmp);
}

int partition(void** array, int len, int size, COMP_FUNC cmp, int* equals) {
	int pivotIdx = len / 2;
	void** pOriginal = adv(array, pivotIdx * size);
	void** pivot = malloc(size);
	memcpy(pivot, pOriginal, size);

	int low = 0;
	int i = 0;
	int high = len - 1;
	*equals = 0;

	while (i <= high) {
		void** element = adv(array, i * size);
		void** toSwap;
		switch(cmp(element, pivot)) {
		case -1:
			toSwap = adv(array, low * size);
			swapElements(toSwap, element, size);
			i++;
			low++;
			break;
		case 1:
			toSwap = adv(array, high * size);
			swapElements(toSwap, element, size);
			high--;
			break;
		case 0:
		default:
			(*equals)++;
			i++;
			break;
		}
	}

	free(pivot);

	return low;
}
