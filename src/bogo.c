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

#include "bogo.h"

void fisherYates(void** array, size_t len, size_t size) {
	for (int i = len - 1; i > 0; i--) {
		int idx = rand() % (i + 1);
		void** a = adv(array, i * size);
		void** b = adv(array, idx * size);
		swapElements(a, b, size);
	}
}

void bogoSort_rand(void** array, size_t len, size_t size, COMP_FUNC cmp) {
	while (!isSorted(array, len, size, cmp)) {
		fisherYates(array, len, size);
	}
}

void bogoSort_det(void** array, size_t len, size_t size, COMP_FUNC cmp) {
}
