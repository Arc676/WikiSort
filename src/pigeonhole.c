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

#include "pigeonhole.h"

void pigeonholeSort(void** array, int len, int size, KEY_FUNC key, int keyCount) {
	if (len < 2) {
		return;
	}
	// allocate pigeon holes
	void** pigeonholes;
	int* pigeonholeCounts;
	setupBuckets(&pigeonholes, &pigeonholeCounts, len, size, keyCount);

	// copy elements to pigeon holes
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		int holeIdx = key(ptr, 0, 0, 0, 0);
		int idx = pigeonholeCounts[holeIdx]++;

		void** dstHole = adv(pigeonholes[holeIdx], idx * size);
		memcpy(dstHole, ptr, size);
		ptr = adv(ptr, size);
	}

	bucketsToList(array, pigeonholes, pigeonholeCounts, size, keyCount, 1);
}
