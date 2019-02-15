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

#ifndef PIGEONHOLE_H
#define PIGEONHOLE_H

#include "wikisort.h"
#include "bucket.h"

/**
 * Sorts an array using a pigeonhole sorting algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param key Key function for the elements
 * @param keyCount The total number of possible keys
 */
void pigeonholeSort(void** array, int len, int size, KEY_FUNC key, int keyCount);

#endif
