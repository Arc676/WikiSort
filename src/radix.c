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

void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, DIGIT_EXT digExt, int offset) {
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
		makeBuckets(array, len, buckets, bucketLengths, size, base, digExt, iteration, offset);

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

void radixSortMSDRec(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, DIGIT_EXT digExt, int offset, int iteration) {
	if (len < 2) {
		return;
	}
	void** maxVal = maxValue(array, len, size, cmp);
	if (!bCmp(base, iteration, maxVal)) {
		return;
	}
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
	makeBuckets(array, len, buckets, bucketLengths, size, base, digExt, iteration, offset);

	// recursively sort buckets
	bucket = buckets;
	for (int i = 0; i < base; i++) {
		radixSortMSDRec(*bucket, bucketLengths[i], size, cmp, base, bCmp, digExt, offset, iteration + 1);
		bucket++;
	}

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

void makeBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, int base, DIGIT_EXT digExt, int iteration, int offset) {
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		int digit = digExt(ptr, base, iteration);
		if (digit >= offset) {
			digit -= offset;
		}
		int idx = bucketLengths[digit]++;

		void** dstBucket = adv(buckets[digit], idx * size);
		memcpy(dstBucket, ptr, size);
		ptr = adv(ptr, size);
	}
}

int int_base_cmp_LSD(int base, int iteration, void** value) {
	int val = *(int*)value;
	return (int)pow(base, iteration) <= val;
}

int int_base_dig_LSD(void** value, int base, int iteration) {
	int val = *(int*)value;
	return (val / (int)pow(base, iteration)) % base;
}

int str_base_cmp_MSD(int base, int iteration, void** value) {
	char* s = *(char**)value;
	int len = strlen(s);
	return iteration < len;
}

int str_base_MSD(void** value, int base, int iteration) {
	char* s = *(char**)value;
	int len = strlen(s);
	if (len <= iteration) {
		return 0;
	}
	return s[iteration];
}

int cmp_strlen(void** a, void** b) {
	char* s1 = *(char**)a;
	char* s2 = *(char**)b;
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	return cmp_int((void**)&l1, (void**)&l2);
}
