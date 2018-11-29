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

#ifndef RADIX_H
#define RADIX_H

#include "wikisort.h"

typedef int BASE_CMP(int base, void** value);

typedef int BASE_DIG(void** value, int base, int basePow);

void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, BASE_DIG baseDigit);

void makeBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, int base, BASE_DIG baseDigit, int basePow);

int int_base_cmp(int base, void** value);

int int_base_dig(void** value, int base, int basePow);

#endif
