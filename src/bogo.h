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

#ifndef BOGO_H
#define BOGO_H

#include "wikisort.h"

typedef struct BogosortPermHandler {
	COMP_FUNC* cmp;
} BogosortPermHandler;

/**
 * Handler function for permutation generator functions; called
 * whenever a new permutation has been generated
 * @param array The array in a new permutation
 * @param len The length of the array
 * @param size The size of a single element
 * @param arg An argument to contain user data; can be used to contain arbitrary information
 * @return Whether the generation of new permutations should be aborted
 */
typedef int PERM_HANDLER(void** array, int len, int size, void* arg);

/**
 * Shuffles the given array using the Fisher Yates algorithm; caller
 * should call srand first
 * @param array The array to shuffle
 * @param len The length of the array
 * @param size The size of a single element
 */
void fisherYates(void** array, int len, int size);

/**
 * Recursively generates new permutations of an array using Heap's Algorithm
 * @param k Number of initial elements from the array to permute
 * @param array The array whose permutations to generate
 * @param len The length of the array
 * @param size The size of a single element
 * @param handler A handler function to be called when each new permutation is generated
 * @param handlerArg The argument to be passed to the handler function
 * @return Whether the generation of new permutations should be aborted
 */
int heapsAlgorithm(int k, void** array, int len, int size, PERM_HANDLER handler, void* handlerArg);

/**
 * Sorts the given array using a randomized bogosort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void bogoSort_rand(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Sorts the given array using a deterministic bogosort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void bogoSort_det(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Permutation handler function for deterministic Bogosort
 * @param array The given permutation
 * @param len The length of the array
 * @param size The size of a single element
 * @param arg The handler argument; should be of type BogosortPermHandler
 */
int bogoSort_permHandler(void** array, int len, int size, void* arg);

#endif
