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

#include "oddeven.h"

void oddEvenSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 1; i < len - 1; i += 2) {
			void** a = adv(array, i * size);
			void** b = adv(array, (i + 1) * size);
			if (cmp(a, b) == 1) {
				swapElements(a, b, size);
				sorted = 0;
			}
		}
		for (int i = 0; i < len - 1; i += 2) {
			void** a = adv(array, i * size);
			void** b = adv(array, (i + 1) * size);
			if (cmp(a, b) == 1) {
				swapElements(a, b, size);
				sorted = 0;
			}
		}

	}
}
