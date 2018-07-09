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

#include "cycle.h"

void cycleSort(void** array, size_t len, size_t size, COMP_FUNC cmp) {
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

void performCycle(void** array, size_t len, size_t size, COMP_FUNC cmp, void** item, int* pos) {
	int start = *pos;
	for (int j = start + 1; j < len; j++) {
		void** b = adv(array, j * size);
		if (cmp(b, item) == -1) {
			(*pos)++;
		}
	}
	// if it needs to be moved
	if (*pos != start) {
		void** toSwap;
		while (1) {
			toSwap = adv(array, *pos * size);
			if (!cmp(item, toSwap)) {
				(*pos)++;
			} else {
				break;
			}
		}
		swapElements(item, toSwap, size);
	}
}