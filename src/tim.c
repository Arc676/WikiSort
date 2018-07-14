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

#include "tim.h"

int computeMinrun(int len) {
	int addition = 0;
	while (len >= 64) {
		addition |= len & 1;
		len >>= 1;
	}
	return len + addition;
}

void reverse(void** array, int len, int size) {
	for (int i = 0;;) {
		void** a = adv(array, i * size);
		void** b = adv(array, (len - i - 1) * size);
		swapElements(a, b, size);
		i++;
		if (i >= len - i - 1) {
			break;
		}
	}
}

void timSort(void** array, int len, int size, COMP_FUNC cmp) {
	// determine minrun length
	int minrun = computeMinrun(len);

	// prepare a list of all the runs
	// each row represents one run
	// each row contains two integers: the start index and the length
	int runs[len / 2 + 1][2];
	int runCount = 0;

	// the kind of run currently being searched for
	int state = NONE;

	// beginning of current run
	int start = 0;

	// search for runs
	int i;
	for (i = 1; i < len; i++) {
		void** prev = adv(array, (i - 1) * size);
		void** current = adv(array, i * size);
		
		// compare current element to its predecessor
		int type = cmp(current, prev) >= 0 ? NONDESCENDING : DESCENDING;
		
		// if the current run isn't done yet
		if (type & state) {
			state = type;
		} else {
			// if the run is complete, store run data
			int rlen = i - start;

			runs[runCount][0] = start;
			runs[runCount][1] = rlen;

			// if it's a descending run, reverse it
			if (state == DESCENDING) {
				void** begin = adv(array, start * size);
				reverse(begin, rlen, size);
			}

			// reset run data
			start = i;
			state = NONE;
			runCount++;
		}
	}
	// check final run
	int rlen = i - start;
	runs[runCount][0] = start;
	runs[runCount][1] = rlen;
	if (state == DESCENDING) {
		void** begin = adv(array, start * size);
		reverse(begin, rlen, size);
	}
	runCount++;

	// combine runs until the entire array is just one run
	while (runCount > 1) {
		// get references to runs
		void** arr1 = adv(array, runs[runCount - 1][0] * size);
		int len1 = runs[runCount - 1][1];

		void** dst = adv(array, runs[runCount - 2][0] * size);
		void** arr2 = dst;
		int len2 = runs[runCount - 2][1];

		// copy the array further to the left into temporary space
		void** temp;
		temp = malloc(len2 * size);
		memcpy(temp, arr2, len2 * size);
		arr2 = temp;

		// merge runs into original memory space
		mergeArrays(
			dst, len1 + len2,
			arr1, len1,
			arr2, len2,
			size, cmp
		);
		free(temp);

		// update references to runs
		runs[runCount - 2][1] += runs[runCount - 1][1];
		runCount--;
	}
}
