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

#ifndef BUCKET_H
#define BUCKET_H

#include "wikisort.h"
#include "quick.h"

/**
 * Type definition for key function for distribution sorts;
 * if the keyCount parameter is 0, determine the total number
 * of buckets required to sort the list using the same key function
 * @param val Value whose key to determine
 * @param minVal Minimum value in the array, as specified by comparison
 * @param maxVal Maximum value in the array, as specified by comparison
 * @param keyCount Total number of keys
 * @param iteration The 0-indexed iteration value during this key calculation
 * @return Integer key for the given value (aligned to 0) or total number of buckets
 */
typedef int KEY_FUNC(void** val, void** minVal, void** maxVal, int keyCount, int iteration);

/**
 * Allocates memory for buckets for distribution sorts
 * @param buckets Pointer to where the bucket array should be stored
 * @param bucketLengths Pointer to where the bucket lengths should be stored
 * @param len The length of the array being sorted
 * @param size The size of a single element in the array
 * @param bucketCount The number of buckets for the sort
 */
void setupBuckets(void*** buckets, int** bucketLengths, int len, int size, int bucketCount);

/**
 * Deallocates memory allocated to buckets for distribution sorts
 * @param buckets Buckets array
 * @param bucketLengths Array of bucket sizes
 * @param bucketCount Number of buckets
 */
void deallocateBuckets(void** buckets, int* bucketLengths, int bucketCount);

/**
 * Iterates through a set of buckets and moves their elements to a destination
 * array such that the destination array contains the buckets' elements sorted by bucket
 * @param dst Destination array
 * @param buckets Array of buckets
 * @param bucketLengths Integer array indicating the number of elements in each bucket
 * @param size The size of a single element in the array
 * @param bucketCount The total number of buckets
 * @param dealloc Whether the bucket memory should be deallocated
 */
void bucketsToList(void** dst, void** buckets, int* bucketLengths, int size, int bucketCount, int dealloc);

/**
 * Copies array elements to a set of buckets based on their key value
 * @param array The array of elements
 * @param len The length of the array
 * @paral buckets Where the buckets are stored
 * @param bucketLengths Integer array in which to store the number of elements copied to each bucket
 * @param size The size of a single element
 * @param key Key function for the elements
 * @param minVal Minimum value in the array, as specified by comparison
 * @param maxVal Maximum value in the array, as specified by comparison
 * @param bucketCount Total number of buckets
 * @param iteration The 0-indexed iteration value for this distribution
 */
void distributeToBuckets(void** array, int len, void** buckets, int* bucketLengths, int size, KEY_FUNC key, void** minVal, void** maxVal, int bucketCount, int iteration);

/**
 * Sorts an array using a bucket sort algorithm which then
 * sorts the buckets using quicksort
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param key Key function for the elements
 */
void bucketSort(void** array, int len, int size, COMP_FUNC cmp, KEY_FUNC key);

/**
 * Key function for sorting integers into buckets based on the range
 * @param val Value whose key to determine
 * @param minVal Minimum value in the array, as specified by comparison
 * @param maxVal Maximum value in the array, as specified by comparison
 * @param bucketCount Total number of buckets
 * @param iteration The 0-indexed iteration value during this key calculation
 * @return Integer key for the given value (aligned to 0) or total number of buckets
 */
int key_intranges(void** val, void** minVal, void** maxVal, int bucketCount, int iteration);

#endif
