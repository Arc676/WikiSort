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

#ifndef SPLAY_H
#define SPLAY_H

#include "wikisort.h"
#include "tree.h"

/**
 * Builds a splay tree from a given array
 * @param array The array whose elements to add to the tree
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @return Pointer to the root node of the newly constructed splay tree
 */
BinaryTreeNode* arrayToSplayTree(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Perform a splay operation on a node in a splay tree
 * @param node Node to move to the tree's root
 */
void splayTree_splay(BinaryTreeNode* node);

/**
 * Rotates a splay tree around a given node in the given direction
 * @param node Node around which to rotate
 * @param dir LNODE or RNODE to rotate left or right
 */
void splayTree_rotate(BinaryTreeNode* node, int dir);

/**
 * Inserts a value into a splay tree and splays that value
 * so it's at the root
 * @param root Node from which to start searching for insertion position
 * @param value Value to insert into the tree
 * @param cmp Element comparison function
 * @return Pointer to the newly inserted node
 */
BinaryTreeNode* splayTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp);

/**
 * Removes a value from a splay tree and splays that node's parent
 * @param node Node to remove from the tree
 */
void splayTree_delete(BinaryTreeNode* node);

/**
 * Finds a value in a splay tree and splays that node
 * @param root Node from which to start searching
 * @param value Value for which to search
 * @param cmp Element comparison function
 * @return Pointer to the found node, if any
 */
BinaryTreeNode* splayTree_find(BinaryTreeNode* root, void** value, COMP_FUNC cmp);

/**
 * Sorts an array using a splaysort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void splaySort(void** array, int len, int size, COMP_FUNC cmp);

#endif
