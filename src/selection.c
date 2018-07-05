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

#include "selection.h"

void selectionSort(void** array, size_t len, size_t size, COMP_FUNC cmp) {
	for (int i = 0; i < len - 1; i++) {
		void** a;
		void** b;
		int minIndex = i;
		for (int j = i + 1; j < len; j++) {
			a = adv(array, j * size);
			b = adv(array, minIndex * size);
			if (cmp(a, b)) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			a = adv(array, i * size);
			b = adv(array, minIndex * size);
			swapElements(a, b, size);
		}
	}
}
