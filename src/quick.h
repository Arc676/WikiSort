//Copyright (C) 2018-9 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef QUICK_H
#define QUICK_H

#include "wikisort.h"

/**
 * Sorts the given array using a quicksort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void quickSort(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Partitions the list by moving elements such that elements
 * are placed relative to a pivot according to size
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param equals Pointer to which to write the number of elements equal to the pivot
 * @return The final position of the pivot element
 */
int partition(void** array, int len, int size, COMP_FUNC cmp, int* equals);

#endif
