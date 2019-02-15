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

#include "wikisort.h"

void** adv(void** start, int dist) {
	#ifdef _32BITMODE
	uint32_t ptr = (uint32_t)start;
	#else
	uint64_t ptr = (uint64_t)start;
	#endif

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
	if (len < 2) {
		return 1;
	}
	void** a = array;
	void** b = adv(array, size);
	for (int i = 0; i < len - 1; i++) {
		if (cmp(a, b) == 1) {
			return 0;
		}
		a = b;
		b = adv(b, size);
	}
	return 1;
}

void** minValue(void** array, int len, int size, COMP_FUNC cmp) {
	void** ptr = adv(array, size);
	void** min = array;
	for (int i = 1; i < len; i++) {
		if (cmp(ptr, min) == -1) {
			min = ptr;
		}
		ptr = adv(ptr, size);
	}
	return min;
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

int binarySearch(void** array, int len, int size, COMP_FUNC cmp, void** search) {
	int left = 0;
	int right = len - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		void** element = adv(array, mid * size);
		switch (cmp(element, search)) {
		case -1:
			left = mid + 1;
			break;
		case 1:
			right = mid - 1;
			break;
		case 0:
		default:
			return mid;
		}
	}
	return -1;
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

int cmp_str(void** a, void** b) {
	char* s1 = *(char**)a;
	char* s2 = *(char**)b;
	int ret = strcmp(s1, s2);
	if (ret < 0) {
		return -1;
	}
	if (ret > 0) {
		return 1;
	}
	return 0;
}
