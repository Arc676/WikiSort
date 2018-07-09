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

#ifndef BOGO_H
#define BOGO_H

#include "wikisort.h"

/**
 * Shuffles the given array using the Fisher Yates algorithm; caller
 * should call srand first
 * @param array The array to shuffle
 * @param len The length of the array
 * @param size The size of a single element
 */
void fisherYates(void** array, size_t len, size_t size);

/**
 * Sorts the given array using a randomized bogosort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Comparison function that returns if an element is smaller than another
 */
void bogoSort_rand(void** array, size_t len, size_t size, COMP_FUNC cmp);

/**
 * Sorts the given array using a deterministic bogosort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Comparison function that returns if an element is smaller than another
 */
void bogoSort_det(void** array, size_t len, size_t size, COMP_FUNC cmp);

#endif
