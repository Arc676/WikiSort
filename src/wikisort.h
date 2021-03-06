//Copyright (C) 2018-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIKISORT_H
#define WIKISORT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#ifdef VISUALIZER

typedef void VISUALIZER_SWAP(void** a, void** b);
typedef void VISUALIZER_ADV(void** ptr, int dist);
typedef void VISUALIZER_UPDATE(void** arr, int len, int size);
typedef int VISUALIZER_ABORT_REQ();

extern VISUALIZER_SWAP* visualizer_itemsSwapped;
extern VISUALIZER_ADV* visualizer_pointerAdvanced;
extern VISUALIZER_UPDATE* visualizer_updateArray;
extern VISUALIZER_ABORT_REQ* visualizer_abortRequested;

#endif

/**
 * Type definition for comparison function to be used
 * by sorting algorithms
 * @param a Pointer to first element
 * @param b Pointer to second element
 * @return -1, 0, or 1 if a < b, a == b, or a > b, respectively
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
void** adv(void** start, int dist);

/**
 * Utility method for swapping two items in a list
 * @param a Pointer to first element
 * @param b Pointer to second element
 * @param size Size of the elements
 */
void swapElements(void** a, void** b, int size);

/**
 * Determines if a list is sorted
 * @param array The array to check
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @return Whether the array is sorted
 */
int isSorted(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Determines the extreme (max or min) value in an array (linear search)
 * @param array The array to search
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Comparison function for the elements
 * @param max Whether the maximum should be searched for (otherwise finds the minimum)
 * @param index A pointer to an integer in which to store the index of the found element (can be NULL)
 * @return Pointer to the maximum value as determined by the comparison function
 */
void** extremeValue(void** array, int len, int size, COMP_FUNC cmp, int max, int* index);

/**
 * Performs a binary search in a list for a given element
 * @param array The array in which to search
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param search The element for which to search
 * @return The index of the searched-for element in the array
 */
int binarySearch(void** array, int len, int size, COMP_FUNC cmp, void** search);

/**
 * Comparison function for integers
 * @param a Pointer to first integer
 * @param b Pointer to second integer
 * @return -1, 0, or 1 if a < b, a == b, or a > b, respectively
 */
int cmp_int(void** a, void** b);

/**
 * Comparison function for floats
 * @param a Pointer to first float
 * @param b Pointer to second float
 * @return -1, 0, or 1 if a < b, a == b, or a > b, respectively
 */
int cmp_float(void** a, void** b);

/**
 * Comparison function for doubles
 * @param a Pointer to first double
 * @param b Pointer to second double
 * @return -1, 0, or 1 if a < b, a == b, or a > b, respectively
 */
int cmp_double(void** a, void** b);

/**
 * Comparison function for strings
 * @param a Pointer to first string
 * @param b Pointer to second string
 * @return Standard library strcmp on the two strings
 */
int cmp_str(void** a, void** b);

#endif

#ifdef __cplusplus
}
#endif
