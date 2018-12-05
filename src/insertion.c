
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

#include "insertion.h"

void insertionSort(void** array, int len, int size, COMP_FUNC cmp) {
	for (int i = 1; i < len; i++) {
		void** a = adv(array, i * size);
		void** b = adv(array, (i - 1) * size);
		for (int j = i; j > 0; j--) {
			// stop when the element is greater than the preceding one
			if (cmp(a, b) == 1) {
				break;
			}
			swapElements(a, b, size);
			a = b;
			b = adv(b, -size);
		}
	}
}
