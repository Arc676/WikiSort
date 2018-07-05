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

void** adv(void** start, size_t dist) {
	uint64_t ptr = (uint64_t)start;
	ptr += dist;
	return (void**)ptr;
}

void swapElements(void** a, void** b, size_t size) {
	void** tmp = malloc(size);
	memcpy(tmp, a, size);
	memmove(a, b, size);
	memmove(b, tmp, size);
	free(tmp);
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
