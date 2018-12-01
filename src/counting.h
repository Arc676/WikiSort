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

#ifndef COUNTING_H
#define COUNTING_H

#include "wikisort.h"

/**
 * Type definition for key function for
 * counting sort
 * @param val Value whose key to determine
 * @return Integer key for the given value
 */
typedef int KEY_FUNC(void** val);

/**
 * Sorts an array using a counting sort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param key Key function for the elements
 * @param keyCount The total number of possible keys (maximum key minus 1)
 */
void countingSort(void** array, int len, int size, KEY_FUNC key, int keyCount);

/**
 * Key function for integers
 * @param val Pointer to the integer
 * @return The given integer
 */
int key_int(void** val);

#endif
