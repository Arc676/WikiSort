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

#ifndef RADIX_H
#define RADIX_H

#include <string.h>

#include "wikisort.h"

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
 * Type definition for digit extraction functions to be
 * used when generating buckets for radix sort
 * @param value The value from which to extract the digit
 * @param base The base for the radix sort (number of possible digits)
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The relevant digit in the value for the radix sort, aligned to zero
 */
typedef int DIGIT_EXT(void** value, int base, int iteration);

/**
 * Sorts an array using a least-significant-digit radix sort
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison element
 * @param base The base for the radix sort (number of possible digits)
 * @param bCmp Base comparison function
 * @param digExt Digit extraction function
 * @param offset Integer value of the lowest digit
 */
void radixSortLSD(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, DIGIT_EXT digExt, int offset);

/**
 * Sorts an array using a recursive most-significant-digit radix sort
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison element
 * @param base The base for the radix sort (number of possible digits)
 * @param bCmp Base comparison function
 * @param digExt Digit extraction function
 * @param offset Integer value of the lowest digit
 * @param iteration Recursion depth
 */
void radixSortMSDRec(void** array, int len, int size, COMP_FUNC cmp, int base, BASE_CMP bCmp, DIGIT_EXT digExt, int offset, int iteration);

/**
 * Separates the elements of a list into buckets
 * based on the digits
 * @param array The array to separate into buckets
 * @param len The length of the array
 * @param buckets Array in which to store the buckets
 * @param bucketLengths Integer array in which to store how many values ended up in each bucket
 * @param size The size of a single element
 * @param base The base for the radix sort (number of possible digits)
 * @param digExt Digit extraction function
 * @param iteration The 0-indexed iteration value for this bucket generation
 * @param offset Integer value of the lowest digit
 */
void makeBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, int base, DIGIT_EXT digExt, int iteration, int offset);

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
 * @param base The base for the radix sort (number of possible digits)
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The digit 'iteration' positions from the end of the value as represented in the given base
 */
int int_base_dig_LSD(void** value, int base, int iteration);

/**
 * Base comparison function for strings
 * @param value The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this comparison
 * @param value The string against which to compare
 * @return Whether the given string has more characters than 'iteration' + 1
 */
int str_base_cmp_MSD(int base, int iteration, void** value);

/**
 * Last-character extraction function for strings
 * @param value Value from which to extract the last character
 * @param base The base (number of possible characters) for the strings
 * @param iteration The 0-indexed iteration value for this extraction
 * @return The character 'iteration' positions from the end of the string
 */
int str_base_MSD(void** value, int base, int iteration);

/**
 * Comparison function for string length
 * @param a Pointer to first string
 * @param b Pointer to second string
 * @return Integer comparison of the strings' lengths
 */
int cmp_strlen(void** a, void** b);

#endif
