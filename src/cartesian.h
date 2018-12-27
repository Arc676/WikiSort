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

#ifndef CARTESIAN_H
#define CARTESIAN_H

#include "wikisort.h"
#include "heap.h"

/**
 * Binary tree structure, implemented as doubly linked nodes,
 * allowing both upward and downward traversal of the tree
 */
typedef struct BinaryTreeNode {
	void** value;
	int size;
	struct BinaryTreeNode* parent;
	struct BinaryTreeNode* leftChild;
	struct BinaryTreeNode* rightChild;
} BinaryTreeNode;

/**
 * Creates a new binary tree node with the given properties
 * @param value Value for the node
 * @param size Element size
 * @param parent Parent node for the new node
 * @param left Left child node for the new node
 * @param right Right child node for the new node
 * @return Pointer to the newly created tree node
 */
BinaryTreeNode* createBinaryTreeNode(void** value, int size, BinaryTreeNode* parent, BinaryTreeNode* left, BinaryTreeNode* right);

/**
 * Deallocates the memory allocated to a binary tree
 * @param root Root node of the binary tree to deallocate
 */
void destroyBinaryTree(BinaryTreeNode* root);

/**
 * Creates a Cartesian tree with the contents of a given array
 * @param array The array from which to build a Cartesian tree
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @return Pointer to the root node of the newly constructed tree
 */
BinaryTreeNode* arrayToCartesianTree(void** array, int len, int size, COMP_FUNC cmp);

void cartesianTreeSort(void** array, int len, int size, COMP_FUNC cmp);

#endif
