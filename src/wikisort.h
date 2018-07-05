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

#ifndef WIKISORT_H
#define WIKISORT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * Type definition for comparison function to be used
 * by sorting algorithms
 * @param a Pointer to first element
 * @param b Pointer to second element
 * @return Whether a <= b
 */
typedef int COMP_FUNC(void** a, void** b);

/**
 * For a given memory location pointed to by void**,
 * returns the address located the specified distance
 * away from the beginning of the memory location
 * @param start Pointer to beginning of memory location
 * @param dist Desired distance from start in bytes
 * @return Address of location at that distance
 */
void** adv(void** start, size_t dist);

/**
 * Comparison function for integers
 * @param a Pointer to first integer
 * @param b Pointer to second integer
 * @return Whether a <= b
 */
int cmp_int(void** a, void** b);

/**
 * Comparison function for floats
 * @param a Pointer to first float
 * @param b Pointer to second float
 * @return Whether a <= b
 */
int cmp_int(void** a, void** b);

#endif
