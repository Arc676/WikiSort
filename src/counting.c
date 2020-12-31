//Copyright (C) 2018-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "counting.h"

void countingSort(void** array, int len, int size, KEY_FUNC key, int keyCount) {
	if (len < 2) {
		return;
	}
	// allocate memory for algorithm components
	int* count = malloc(keyCount * sizeof(int));
	memset(count, 0, keyCount * sizeof(int));

	void** arrCopy = malloc(len * size);
	memcpy(arrCopy, array, len * size);

	// determine key frequencies
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		count[key(ptr, 0, 0, 0, 0)]++;
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
		int keyVal = key(ptr, 0, 0, 0, 0);
		void** dst = adv(array, count[keyVal] * size);
		memcpy(dst, ptr, size);

		#ifdef VISUALIZER
		visualizer_updateArray(dst, 1, size);

		if (visualizer_abortRequested()) {
			break;
		}
		#endif

		count[keyVal]++;
		ptr = adv(ptr, size);
	}

	// deallocate temporary storage
	free(arrCopy);
	free(count);
}

int key_int(void** val, void** minVal, void** maxVal, int keyCount, int iteration) {
	return *(int*)val;
}
