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

#ifndef PATIENCE_H
#define PATIENCE_H

#include "wikisort.h"
#include "bucket.h"
#include "merge.h"
#include "tim.h"

/**
 * Sorts an array using a patience sort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param geq GEQ element comparison function (see geq_int)
 */
void patienceSort(void** array, int len, int size, COMP_FUNC cmp, COMP_FUNC geq);

/**
 * Recursively merges multiple arrays into a single array
 * using a divide and conquer algorithm
 * @param dst Destination array into which to copy the elements from the subarrays
 * @param len Length of destination array
 * @param subarrays List of subarrays to merge
 * @param subarrayCount Number of subarrays to merge
 * @param subarrayLengths Array of lengths of each subarray
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void kWayMerge(void** dst, int len, void** subarrays, int subarrayCount, int* subarrayLengths, int size, COMP_FUNC cmp);

/**
 * GEQ comparison function for patience sort for integers
 * (treats a > b as equality)
 * @param a First element
 * @param b Second element
 * @return -1 or 0 if a < b or a >= b, respectively
 */
int geq_int(void** a, void** b);

#endif
