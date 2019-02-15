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

#ifndef CARTESIAN_H
#define CARTESIAN_H

#include "wikisort.h"
#include "tree.h"
#include "heap.h"

/**
 * Creates a Cartesian tree with the contents of a given array
 * with the minimum value at the root of the tree
 * @param array The array from which to build a Cartesian tree
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @return Pointer to the root node of the newly constructed tree
 */
BinaryTreeNode* arrayToCartesianTree(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Sorts an array using a Cartesian sort algorithm with a Cartesian tree
 * and priority queue (heap) with the minimum value at the root
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param binTreeCmp Element comparison function where the elements are stored in the value property of a binary tree node
 */
void cartesianTreeSort(void** array, int len, int size, COMP_FUNC cmp, COMP_FUNC binTreeCmp);

/**
 * Binary tree node element comparison function for integers;
 * NOTE: The Cartesian tree sort algorithm requires that the priority queue
 * hold the minimum value at the root, but the heap implementation has the
 * maximum element at the root, so this function returns the arithmetic
 * opposite of the standard integer comparison function
 * @param a First binary tree node
 * @param b Second binary tree node
 * @return -1, 0, or 1 if the integer stored in the first node is greater than, equal to, or less than that in the second node, respectively
 */
int binTree_cmp_int(void** a, void** b);

#endif
