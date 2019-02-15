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

// Based on GPLv3 Python algorithm found here:
// https://gist.github.com/nandajavarma/a3a6b62f34e74ec4c31674934327bbd3

#ifndef TIM_H
#define TIM_H

// bitwise constants for run type
// when no run is being considered, any following element is acceptable
#define DESCENDING 	0b01
#define NONDESCENDING	0b10
#define NONE		0b11

#include "insertion.h"
#include "merge.h"

/**
 * Computes minrun for Timsort (based on GPLv3 Octave algorithm
 * found here: http://hg.savannah.gnu.org/hgweb/octave/file/0486a29d780f/liboctave/util/oct-sort.cc)
 * @param len Array length
 * @return Good value for minrun
 */
int computeMinrun(int len);

/**
 * Reverses an array
 * @param array Array to reverse
 * @param len Length of array
 * @param size Size of a single element
 */
void reverse(void** array, int len, int size);

/**
 * Sorts the given array using a timsort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void timSort(void** array, int len, int size, COMP_FUNC cmp);

#endif
