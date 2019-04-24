//Copyright (C) 2019 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

//Based on code available from Rosetta Code under the GNU Free Documentation license
//https://rosettacode.org/wiki/Sorting_algorithms/Pancake_sort#C

#include "pancake.h"

void pancakeSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	for (int i = len; i > 1; i--) {
		int maxpos;
		extremeValue(array, i, size, cmp, 1, &maxpos);
		if (maxpos == i - 1) {
			continue;
		}
		if (maxpos != 0) {
			reverse(array, maxpos + 1, size);
		}
		reverse(array, i, size);
	}
}
