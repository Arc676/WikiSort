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

#include "bogo.h"

void fisherYates(void** array, int len, int size) {
	for (int i = len - 1; i > 0; i--) {
		int idx = rand() % (i + 1);
		void** a = adv(array, i * size);
		void** b = adv(array, idx * size);
		swapElements(a, b, size);
	}
}

int heapsAlgorithm(int k, void** array, int len, int size, PERM_HANDLER handler, void* handlerArg) {
	if (k == 1) {
		return handler(array, len, size, handlerArg);
	}
	if (heapsAlgorithm(k - 1, array, len, size, handler, handlerArg)) {
		return 1;
	}
	for (int i = 0; i < k - 1; i++) {
		void** b = adv(array, (k - 1) * size);
		if (k % 2 == 0) {
			void** a = adv(array, i * size);
			swapElements(a, b, size);
		} else {
			swapElements(array, b, size);
		}
		if (heapsAlgorithm(k - 1, array, len, size, handler, handlerArg)) {
			return 1;
		}
	}
	return 0;
}

void bogoSort_rand(void** array, int len, int size, COMP_FUNC cmp) {
	while (!isSorted(array, len, size, cmp)) {
		fisherYates(array, len, size);
	}
}

void bogoSort_det(void** array, int len, int size, COMP_FUNC cmp) {
	BogosortPermHandler bph = { cmp };
	heapsAlgorithm(len, array, len, size, bogoSort_permHandler, &bph);
}

int bogoSort_permHandler(void** array, int len, int size, void* arg) {
	COMP_FUNC* cmp = ((BogosortPermHandler*)arg)->cmp;
	return isSorted(array, len, size, cmp);
}
