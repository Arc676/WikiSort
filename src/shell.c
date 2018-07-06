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

#include "shell.h"

const int ciuraSequence[8] = {
	701, 301, 132, 57, 23, 10, 4, 1
};

GAP_GEN *gapSeqs[GAP_COUNT] = {
	gShell,
	gFrank_Lazarus,
	gA168604,
	gA083318,
	gA003586,
	gA003462,
	gA036569,
	gA036562,
	gA033622,
	gGonnet_BaezaYates,
	gA108870,
	gA102549,
};

void shellSort(void** array, size_t len, size_t size, COMP_FUNC cmp, GapSequence seq) {
	int gapCount = 0;
	int* gaps = gapSeqs[seq](len, &gapCount);
	for (int i = 0; i < gapCount; i++) {
		int gap = gaps[i];
		for (int j = gap; j < len; j++) {
			void** toInsert = malloc(size);
			memcpy(toInsert, adv(array, j * size), size);
			void** dst;
			int k;
			for (k = j; k >= gap; k -= gap) {
				dst = adv(array, k * size);
				void** src = adv(array, (k - gap) * size);
				if (cmp(src, toInsert) != 1) {
					break;
				}
				memcpy(dst, src, size);
			}
			dst = adv(array, k * size);
			memcpy(dst, toInsert, size);
		}
	}
}

// Shell, 1959
int* gShell(int len, int* count) {
	int gapCount = (int)log2f((float)len);
	int* gaps = malloc(gapCount * sizeof(int));
	for (int k = 1; k <= gapCount; k++) {
		gaps[k - 1] = (int)floor(len / pow(2, (double)k));
	}
	*count = gapCount;
	return gaps;
}

int* gFrank_Lazarus(int len, int* count) {
	return 0;
}

// Hibbard, 1963
int* gA168604(int len, int* count) {
	int gapCount = (int)log2f((float)len + 1);
	// omit last gap if length is one less than a power of 2
	if ((int)pow(2, gapCount) - 1 >= len) {
		gapCount--;
	}
	int* gaps = malloc(gapCount * sizeof(int));
	for (int k = gapCount; k > 0; k--) {
		gaps[k - 1] = (int)pow(2, gapCount - k + 1) - 1;
	}
	*count = gapCount;
	return gaps;
}

// Papernov and Stasevich, 1965
int* gA083318(int len, int* count) {
	int gapCount = (int)log2f((float)len - 1);
	// omit last gap if length is one more than a power of 2
	if ((int)pow(2, gapCount) + 1 >= len) {
		gapCount--;
	}
	// add one for the prefixed 1
	gapCount++;
	int* gaps = malloc(gapCount * sizeof(int));
	gaps[gapCount - 1] = 1;
	for (int k = gapCount - 1; k > 0; k--) {
		gaps[k - 1] = (int)pow(2, gapCount - k) + 1;
	}
	*count = gapCount;
	return gaps;
}

int* gA003586(int len, int* count) {
	return 0;
}

int* gA003462(int len, int* count) {
	return 0;
}

int* gA036569(int len, int* count) {
	return 0;
}

int* gA036562(int len, int* count) {
	return 0;
}

int* gA033622(int len, int* count) {
	return 0;
}

// Gonnet and Baeza-Yates, 1991
int* gGonnet_BaezaYates(int len, int* count) {
	int gapCount = (int)(logf((float)len) / logf(11.0/5));
	int* gaps = malloc(gapCount * sizeof(int));
	gaps[0] = len * 5 / 11;
	int i = 1;
	for (; i < gapCount; i++) {
		gaps[i] = gaps[i - 1] * 5 / 11;
		if (gaps[i] == 1) {
			break;
		}
	}
	*count = i + 1;
	return gaps;
}

int* gA108870(int len, int* count) {
	return 0;
}

// Ciura, 2001
int* gA102549(int len, int* count) {
	*count = 8;
	int* gaps = malloc(8 * sizeof(int));
	memcpy(gaps, ciuraSequence, 8 * sizeof(int));
	return gaps;
}

