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

#include "radix.h"

void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, BASE_DIG baseDigit) {
	void** maxVal = maxValue(array, len, size, cmp);
	for (int iteration = 0; bCmp(base, iteration, maxVal); iteration++) {
		// allocate bucket memory
		void** buckets = malloc(base * sizeof(void*));
		void** bucket = buckets;
		for (int i = 0; i < base; i++) {
			*bucket = malloc(len * size);
			bucket++;
		}
		int* bucketLengths = malloc(base * sizeof(int));
		memset(bucketLengths, 0, base * sizeof(int));

		// create buckets from list elements
		makeBuckets(array, len, buckets, bucketLengths, size, base, baseDigit, iteration);

		// sequentially copy values from buckets back into original list
		// and free bucket memory
		void** ptr = array;
		for (int i = 0; i < base; i++) {
			for (int j = 0; j < bucketLengths[i]; j++) {
				void** val = adv(buckets[i], j * size);
				memcpy(ptr, val, size);
				ptr = adv(ptr, size);
			}
			free(buckets[i]);
		}
		free(buckets);
		free(bucketLengths);
	}
}

void makeBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, int base, BASE_DIG baseDigit, int iteration) {
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		int digit = baseDigit(ptr, base, iteration);
		int idx = bucketLengths[digit]++;

		void** dstBucket = adv(buckets[digit], idx * size);
		memcpy(dstBucket, ptr, size);
		ptr = adv(ptr, size);
	}
}

int int_base_cmp(int base, int iteration, void** value) {
	int val = *(int*)value;
	return (int)pow(base, iteration) <= val;
}

int int_base_dig(void** value, int base, int iteration) {
	int val = *(int*)value;
	return (val / (int)pow(base, iteration)) % base;
}
