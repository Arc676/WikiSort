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

#include "intro.h"

void introSort(void** array, int len, int size, COMP_FUNC cmp) {
	int depth = 2 * (int)log2f(len);
	introSort_rec(array, len, size, cmp, depth);
}

void introSort_rec(void** array, int len, int size, COMP_FUNC cmp, int depth) {
	if (len < 2) {
		return;
	}

	#ifdef VISUALIZER
	if (visualizer_abortRequested()) {
		return;
	}
	#endif

	int equals;
	int pivot = partition(array, len, size, cmp, &equals);
	if (depth == 0) {
		heapSort(array, len, size, cmp);
	} else {
		introSort_rec(array, pivot, size, cmp, depth - 1);

		#ifdef VISUALIZER
		visualizer_updateArray(array, pivot, size);
		#endif

		void** right = adv(array, (pivot + equals) * size);
		int rLength = len - pivot - equals;
		introSort_rec(right, rLength, size, cmp, depth - 1);

		#ifdef VISUALIZER
		visualizer_updateArray(right, rLength, size);
		#endif
	}
}
