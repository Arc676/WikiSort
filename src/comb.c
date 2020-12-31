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

#include "comb.h"

void combSort(void** array, int len, int size, COMP_FUNC cmp, float shrink) {
	if (len < 2) {
		return;
	}
	int gapCount;
	int* gaps = gShrinkFactor(len, &gapCount, shrink);
	int gapIndex = 0;
	int sorted = 0;
	while (!sorted) {
		int gap;
		if (gapIndex < gapCount - 1) {
			sorted = 0;
			gap = gaps[gapIndex++];
		} else {
			sorted = 1;
			gap = 1;
		}
		void** a = array;
		void** b = adv(array, gap * size);
		for (int i = 0; i + gap < len; i++) {
			if (cmp(a, b) == 1) {
				swapElements(a, b, size);
				sorted = 0;

				#ifdef VISUALIZER
				visualizer_updateArray(a, gap + 1, size);
				#endif
			}
			a = adv(a, size);
			b = adv(b, size);
		}
	}
	free(gaps);
}
