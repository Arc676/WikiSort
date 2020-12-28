//Copyright (C) 2018-20 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

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

#ifndef RADIX_H
#define RADIX_H

#include "wikisort.h"
#include "bucket.h"

/**
 * Type definition for base comparison functions to be
 * used by radix sort to determine whether the sorting process is complete
 * @param base The base for the radix sort (number of possible digits)
 * @param iteration The 0-indexed iteration value for this comparison
 * @param value The value against which to compare
 * @return Whether the radix sort should run this iteration
 */
typedef int BASE_CMP(int base, int iteration, void** value);

/**
 * Sorts an array using a least-significant-digit radix sort
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param base The base for the radix sort (number of possible digits)
 * @param bCmp Base comparison function
 * @param digExt Digit extraction function
 */
void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, KEY_FUNC digExt);

/**
 * Sorts an array using a recursive most-significant-digit radix sort
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param base The base for the radix sort (number of possible digits)
 * @param bCmp Base comparison function
 * @param digExt Digit extraction function
 * @param iteration Recursion depth
 */
void radixSortMSDRec(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, KEY_FUNC digExt, int iteration);

/**
 * Base comparison function for integers
 * @param base The base for the numbers
 * @param iteration The 0-indexed iteration value for this comparison
 * @param value The value against which to compare
 * @return Whether pow(base, iteration) does not exceed the value
 */
int int_base_cmp_LSD(int base, int iteration, void** value);

/**
 * LSD extraction function for integers
 * @param value Value from which to extract digit
 * @param minVal Minimum value in the array, as specified by comparison (unused)
 * @param maxVal Maximum value in the array, as specified by comparison (unused)
 * @param base The base for the radix sort (number of possible digits)
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The digit 'iteration' positions from the end of the value as represented in the given base
 */
int int_base_dig_LSD(void** value, void** minVal, void** maxVal, int base, int iteration);

/**
 * Base comparison function for strings
 * @param value The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this comparison
 * @param value The string against which to compare
 * @return Whether the given string has more characters than 'iteration' + 1
 */
int str_base_cmp_MSD(int base, int iteration, void** value);

/**
 * Last-character extraction function for strings; this function
 * does not perform any alignment; when sorting, define a new function
 * with offset or use one of the provided ones
 * @param value Value from which to extract the last character
 * @param minVal Minimum value in the array, as specified by comparison (unused)
 * @param maxVal Maximum value in the array, as specified by comparison (unused)
 * @param base The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The character 'iteration' positions from the end of the string
 */
int str_base_MSD_unaligned(void** value, void** minVal, void** maxVal, int base, int iteration);

/**
 * Last-character extraction function for strings, aligned to 'a'
 * (use when array only contains all lowercase strings)
 * @param value Value from which to extract the last character
 * @param minVal Minimum value in the array, as specified by comparison (unused)
 * @param maxVal Maximum value in the array, as specified by comparison (unused)
 * @param base The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The character 'iteration' positions from the end of the string
 */
int str_base_MSD_lowercase(void** value, void** minVal, void** maxVal, int base, int iteration);

/**
 * Last-character extraction function for strings, aligned to 'A'
 * (use when array only contains all uppercase strings)
 * @param value Value from which to extract the last character
 * @param minVal Minimum value in the array, as specified by comparison (unused)
 * @param maxVal Maximum value in the array, as specified by comparison (unused)
 * @param base The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The character 'iteration' positions from the end of the string
 */
int str_base_MSD_uppercase(void** value, void** minVal, void** maxVal, int base, int iteration);

/**
 * Last-character extraction function for strings, case insensitive
 * (aligns to 'a' or 'A' depending on case)
 * @param value Value from which to extract the last character
 * @param minVal Minimum value in the array, as specified by comparison (unused)
 * @param maxVal Maximum value in the array, as specified by comparison (unused)
 * @param base The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The character 'iteration' positions from the end of the string
 */
int str_base_MSD_ignoreCase(void** value, void** minVal, void** maxVal, int base, int iteration);

/**
 * Comparison function for string length
 * @param a Pointer to first string
 * @param b Pointer to second string
 * @return Integer comparison of the strings' lengths
 */
int cmp_strlen(void** a, void** b);

#endif

#ifdef __cplusplus
}
#endif
