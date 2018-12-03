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

#include "bucket.h"

void setupBuckets(void*** buckets, int** bucketLengths, int len, int size, int bucketCount) {
	// allocate bucket memory
	*buckets = malloc(bucketCount * sizeof(void*));
	void** bucket = *buckets;
	for (int i = 0; i < bucketCount; i++) {
		*bucket = malloc(len * size);
		bucket++;
	}
	*bucketLengths = malloc(bucketCount * sizeof(int));
	memset(*bucketLengths, 0, bucketCount * sizeof(int));
}

void bucketsToList(void** dst, void** buckets, int* bucketLengths, int size, int bucketCount, int dealloc) {
	void** ptr = dst;
	for (int i = 0; i < bucketCount; i++) {
		for (int j = 0; j < bucketLengths[i]; j++) {
			void** val = adv(buckets[i], j * size);
			memcpy(ptr, val, size);
			ptr = adv(ptr, size);
		}
		if (dealloc) free(buckets[i]);
	}
	if (dealloc) {
		free(buckets);
		free(bucketLengths);
	}
}

void bucketSort(void** array, int len, int size, COMP_FUNC cmp, KEY_FUNC key) {
	if (len < 2) {
		return;
	}
	// allocate bucket memory
	void** minVal = minValue(array, len, size, cmp);
	void** maxVal = maxValue(array, len, size, cmp);
	int bucketCount = key(0, minVal, maxVal, 0, 0) + 1;
	void** buckets;
	int* bucketLengths;
	setupBuckets(&buckets, &bucketLengths, len, size, bucketCount);

	// create buckets from list elements
	distributeToBuckets(array, len, buckets, bucketLengths, size, key, minVal, maxVal, bucketCount, 0);

	// sort buckets using quicksort
	void** bucket = buckets;
	for (int i = 0; i < bucketCount; i++) {
		quickSort(*bucket, bucketLengths[i], size, cmp);
		bucket++;
	}

	bucketsToList(array, buckets, bucketLengths, size, bucketCount, 1);
}

void distributeToBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, KEY_FUNC key, void** minVal, void** maxVal, int bucketCount, int iteration) {
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		int bucketIdx = key(ptr, minVal, maxVal, bucketCount, iteration);
		int idx = bucketLengths[bucketIdx]++;

		void** dstBucket = adv(buckets[bucketIdx], idx * size);
		memcpy(dstBucket, ptr, size);
		ptr = adv(ptr, size);
	}
}

int key_intranges(void** val, void** minVal, void** maxVal, int bucketCount, int iteration) {
	int minV = *(int*)minVal;
	int maxV = *(int*)maxVal;
	int range = maxV - minV;
	int bucketRange = range / 10;
	if (bucketCount == 0) {
		return range / bucketRange + 1;
	}
	int value = *(int*)val;
	return (value - minV) / bucketRange;
}
