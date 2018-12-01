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

#include "counting.h"

void countingSort(void** array, int len, int size, KEY_FUNC key, int keyCount) {
	// allocate memory for algorithm components
	int* count = malloc(keyCount * sizeof(int));
	memset(count, 0, keyCount * sizeof(int));

	void** arrCopy = malloc(len * size);
	memcpy(arrCopy, array, len * size);

	// determine key frequencies
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		count[key(ptr)]++;
		ptr = adv(ptr, size);
	}

	// determine starting index for each key
	int pos = 0;
	for (int i = 0; i < keyCount; i++) {
		pos += count[i];
		count[i] = pos - count[i];
	}

	// rewrite array in sorted order
	ptr = arrCopy;
	for (int i = 0; i < len; i++) {
		int keyVal = key(ptr);
		memcpy(adv(array, count[keyVal] * size), ptr, size);
		count[keyVal]++;
		ptr = adv(ptr, size);
	}

	// deallocate temporary storage
	free(arrCopy);
	free(count);
}

int key_int(void** val) {
	return *(int*)val;
}
