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

void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, KEY_FUNC digExt) {
	void** maxVal = maxValue(array, len, size, cmp);
	for (int iteration = 0; bCmp(base, iteration, maxVal); iteration++) {
		// allocate bucket memory
		void** buckets;
		int* bucketLengths;
		setupBuckets(&buckets, &bucketLengths, len, size, base);

		// create buckets from list elements
		distributeToBuckets(array, len, buckets, bucketLengths, size, digExt, 0, 0, base, iteration);

		bucketsToList(array, buckets, bucketLengths, size, base, 1);
	}
}

void radixSortMSDRec(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, KEY_FUNC digExt, int iteration) {
	if (len < 2) {
		return;
	}
	void** maxVal = maxValue(array, len, size, cmp);
	if (!bCmp(base, iteration, maxVal)) {
		return;
	}
	// allocate bucket memory
	void** buckets;
	int* bucketLengths;
	setupBuckets(&buckets, &bucketLengths, len, size, base);

	// create buckets from list elements
	distributeToBuckets(array, len, buckets, bucketLengths, size, digExt, 0, 0, base, iteration);

	// recursively sort buckets
	void** bucket = buckets;
	for (int i = 0; i < base; i++) {
		radixSortMSDRec(*bucket, bucketLengths[i], size, cmp, base, bCmp, digExt, iteration + 1);
		bucket++;
	}

	bucketsToList(array, buckets, bucketLengths, size, base, 0);
}

int int_base_cmp_LSD(int base, int iteration, void** value) {
	int val = *(int*)value;
	return (int)pow(base, iteration) <= val;
}

int int_base_dig_LSD(void** value, void** minVal, void** maxVal, int base, int iteration) {
	if (base == 0) {
		return 10;
	}
	int val = *(int*)value;
	return (val / (int)pow(base, iteration)) % base;
}

int str_base_cmp_MSD(int base, int iteration, void** value) {
	char* s = *(char**)value;
	int len = strlen(s);
	return iteration < len;
}

int str_base_MSD_unaligned(void** value, void** minVal, void** maxVal, int base, int iteration) {
	if (base == 0) {
		return 26;
	}
	char* s = *(char**)value;
	int len = strlen(s);
	if (len <= iteration) {
		return 0;
	}
	return s[iteration];
}

int str_base_MSD_lowercase(void** value, void** minVal, void** maxVal, int base, int iteration) {
	return str_base_MSD_unaligned(value, 0, 0, base, iteration) - 'a';
}

int str_base_MSD_uppercase(void** value, void** minVal, void** maxVal, int base, int iteration) {
	return str_base_MSD_unaligned(value, 0, 0, base, iteration) - 'A';
}

int str_base_MSD_ignoreCase(void** value, void** minVal, void** maxVal, int base, int iteration) {
	int c = str_base_MSD_unaligned(value, 0, 0, base, iteration);
	if ('a' <= c && c <= 'z') {
		return c - 'a';
	} else if ('A' <= c && c <= 'Z') {
		return c - 'A';
	}
	return 0;
}

int cmp_strlen(void** a, void** b) {
	char* s1 = *(char**)a;
	char* s2 = *(char**)b;
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	return cmp_int((void**)&l1, (void**)&l2);
}
