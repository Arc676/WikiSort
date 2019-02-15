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

#include "stooge.h"

void stoogeSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	void** b = adv(array, (len - 1) * size);
	if (cmp(array, b) == 1) {
		swapElements(array, b, size);
	}
	if (len > 2) {
		// obtain 1/3 the length of the list
		int _13len = len / 3;
		// obtain 2/3 the length of the list
		int _23len = len - _13len;

		void** second2_3 = adv(array, _13len * size);
		stoogeSort(array, _23len, size, cmp);
		stoogeSort(second2_3, _23len, size, cmp);
		stoogeSort(array, _23len, size, cmp);
	}
}
