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

#include "cocktail.h"

void cocktailSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	int sorted;
	int passes = 0;
	void** a;
	void** b;
	do {
		sorted = 1;
		a = adv(array, passes * size);
		b = adv(array, (passes + 1) * size);
		for (int i = passes; i < len - 2 - passes; i++) {
			if (cmp(a, b) == 1) {
				swapElements(a, b, size);
				sorted = 0;
			}
			a = b;
			b = adv(b, size);
		}
		if (sorted) {
			break;
		}
		a = adv(array, (len - 2 - passes) * size);
		b = adv(array, (len - 1 - passes) * size);
		for (int i = len - 2 - passes; i >= passes; i--) {
			if (cmp(a, b) == 1) {
				swapElements(a, b, size);
				sorted = 0;
			}
			b = a;
			a = adv(a, -size);
		}
		passes++;
	} while (!sorted);
}
