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

#include "patience.h"

void patienceSort(void** array, int len, int size, COMP_FUNC cmp, COMP_FUNC geq) {
	if (len < 2) {
		return;
	}
	int pileCount = 0;
	void** piles;
	int* pileSizes;
	setupBuckets(&piles, &pileSizes, len, size, len);

	void** pileTops = malloc(len * size);

	void** element = array;
	for (int i = 0; i < len; i++) {
		// find destination pile
		int dstPile = binarySearch(pileTops, pileCount, size, geq, element);
		if (dstPile < 0) {
			dstPile = pileCount++;
		}

		// copy to pile
		int pileIdx = pileSizes[dstPile]++;
		void** dst = adv(piles[dstPile], pileIdx * size);
		memcpy(dst, element, size);

		// update top card for pile
		dst = adv(pileTops, dstPile * size);
		memcpy(dst, element, size);

		// move to next element in array
		element = adv(element, size);

		#ifdef VISUALIZER
		if (visualizer_abortRequested()) {
			break;
		}
		#endif
	}

	// reverse piles
	for (int i = 0; i < pileCount; i++) {
		reverse(piles[i], pileSizes[i], size);

		#ifdef VISUALIZER
		if (visualizer_abortRequested()) {
			break;
		}
		#endif
	}

	kWayMerge(array, len, piles, pileCount, pileSizes, size, cmp);

	deallocateBuckets(piles, pileSizes, len);
	free(pileTops);
}

void kWayMerge(void** dst, int len, void** subarrays, int subarrayCount, int* subarrayLengths, int size, COMP_FUNC cmp) {
	if (subarrayCount < 2) {
		if (subarrayCount == 1) {
			memcpy(dst, subarrays[0], len * size);
		}
	} else if (subarrayCount == 2) {
		mergeArrays(dst, len, subarrays[0], subarrayLengths[0], subarrays[1], subarrayLengths[1], size, cmp);
	} else {
		int len1 = 0;
		int half1 = subarrayCount / 2;

		int len2 = 0;
		int half2 = subarrayCount - half1;

		for (int i = 0; i < subarrayCount; i++) {
			if (i < half1) {
				len1 += subarrayLengths[i];
			} else {
				len2 += subarrayLengths[i];
			}
		}

		void** sub1 = malloc(len1 * size);
		kWayMerge(sub1, len1, subarrays, half1, subarrayLengths, size, cmp);

		void** sub2 = malloc(len2 * size);
		kWayMerge(sub2, len2, subarrays + half1, half2, subarrayLengths + half1, size, cmp);

		mergeArrays(dst, len, sub1, len1, sub2, len2, size, cmp);

		free(sub1);
		free(sub2);
	}
}

int geq_int(void** a, void** b) {
	int x = *(int*)a;
	int y = *(int*)b;
	if (x < y) {
		return -1;
	}
	return 0;
}
