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

#include "selection.h"

void selectionSort(void** array, int len, int size, COMP_FUNC cmp) {
	for (int i = 0; i < len - 1; i++) {
		void** a = adv(array, (i + 1) * size);
		void** b = adv(array, i * size);
		int minIndex = i;
		for (int j = i + 1; j < len; j++) {
			if (cmp(a, b) <= 0) {
				minIndex = j;
				b = a;
			}
			a = adv(a, size);
		}
		if (minIndex != i) {
			a = adv(array, i * size);
			swapElements(a, b, size);
		}
	}
}
