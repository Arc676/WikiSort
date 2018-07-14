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

#ifndef MERGE_H
#define MERGE_H

#include "wikisort.h"

/**
 * Sorts the given array using a merge sort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void mergeSort(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Merges two arrays into a third array, sorting the elements
 * @param dst Array into which to copy the elements
 * @param len Length of destination array
 * @param arr1 First array to copy
 * @param len1 Length of first array
 * @param arr2 Second array to copy
 * @param len2 Length of second array
 * @param size Element size for the arrays
 * @param cmp Element comparison function
 */
void mergeArrays(void** dst, int len, void** arr1, int len1, void** arr2, int len2, int size, COMP_FUNC cmp);

#endif
