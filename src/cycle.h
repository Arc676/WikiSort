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

#ifndef CYCLE_H
#define CYCLE_H

#include "wikisort.h"

/**
 * Sorts the given array using a cycle sort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void cycleSort(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Utility function for performing the cycle sort algorithm's repeated
 * section to avoid code duplication
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param item The item currently being moved
 * @param pos Pointer to position in array currently being checked
 */
void performCycle(void** array, int len, int size, COMP_FUNC cmp, void** item, int* pos);

#endif
