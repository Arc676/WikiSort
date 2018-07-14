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

#include "bubble.h"

void bubbleSort(void** array, int len, int size, COMP_FUNC cmp) {
	int sorted;
	do {
		sorted = 1;
		for (int i = 0; i < len - 2 - i; i++) {
			void** a = adv(array, i * size);
			void** b = adv(array, (i + 1) * size);
			// if the earlier element is greater than its successor
			if (cmp(a, b) == 1) {
				sorted = 0;
				swapElements(a, b, size);
			}
		}
	} while (!sorted);
}
