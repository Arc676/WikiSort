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

#include "cycle.h"

void cycleSort(void** array, int len, int size, COMP_FUNC cmp) {
	for (int i = 0; i < len - 1; i++) {
		void** item = adv(array, i * size);
		int pos = i;
		performCycle(array, len, size, cmp, item, &pos);
		while (pos != i) {
			pos = i;
			performCycle(array, len, size, cmp, item, &pos);
		}
	}
}

void performCycle(void** array, int len, int size, COMP_FUNC cmp, void** item, int* pos) {
	int start = *pos;
	void** b = adv(array, (start + 1) * size);
	for (int j = start + 1; j < len; j++) {
		if (cmp(b, item) == -1) {
			(*pos)++;
		}
		b = adv(b, size);
	}
	// if it needs to be moved
	if (*pos != start) {
		void** toSwap = adv(array, *pos * size);
		while (1) {
			if (!cmp(item, toSwap)) {
				toSwap = adv(toSwap, size);
			} else {
				break;
			}
		}
		swapElements(item, toSwap, size);
	}
}
