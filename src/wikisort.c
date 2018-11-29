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

#include "wikisort.h"

void** adv(void** start, int dist) {
	uint64_t ptr = (uint64_t)start;
	ptr += dist;
	return (void**)ptr;
}

void swapElements(void** a, void** b, int size) {
	void** tmp = malloc(size);
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
}

int isSorted(void** array, int len, int size, COMP_FUNC cmp) {
	for (int i = 0; i < len - 1; i++) {
		void** a = adv(array, i * size);
		void** b = adv(array, (i + 1) * size);
		if (cmp(a, b) == 1) {
			return 0;
		}
	}
	return 1;
}

void** maxValue(void** array, int len, int size, COMP_FUNC cmp) {
	void** ptr = adv(array, size);
	void** max = array;
	for (int i = 1; i < len; i++) {
		if (cmp(ptr, max) == 1) {
			max = ptr;
		}
		ptr = adv(ptr, size);
	}
	return max;
}

int cmp_int(void** a, void** b) {
	int x = *(int*)a;
	int y = *(int*)b;
	if (x > y) {
		return 1;
	}
	if (x < y) {
		return -1;
	}
	return 0;
}

int cmp_float(void** a, void** b) {
	float x = *(float*)a;
	float y = *(float*)b;
	if (x > y) {
		return 1;
	}
	if (x < y) {
		return -1;
	}
	return 0;
}

int cmp_double(void** a, void** b) {
	double x = *(double*)a;
	double y = *(double*)b;
	if (x > y) {
		return 1;
	}
	if (x < y) {
		return -1;
	}
	return 0;
}
