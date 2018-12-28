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

#ifndef TREE_H
#define TREE_H

#include "wikisort.h"

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
 * Adds the elements of a binary tree to a destination array
 * through an in-order traversal of the tree
 * @param root Root node of the tree to traverse
 * @param dst Destination for the tree's contents
 * @return Number of nodes traversed
 */
int inOrderTraversal(BinaryTreeNode* root, void** dst);

/**
 * Builds a binary search tree containing the elements of an array
 * @param array The array whose elements to insert into the tree
 * @param len The length of the array
 * @param size The size of the array
 * @param cmp Element comparison function
 */
BinaryTreeNode* arrayToBinaryTree(void** array, int len, int size, COMP_FUNC cmp);

/**
 * Inserts a value into a binary tree
 * @param root Node from which to start searching for the insertion position
 * @param value The value to insert
 * @param cmp Element comparison function
 */
void binaryTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp);

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
 * Sorts an array using a tree sort method, employing
 * in-order traversal of a binary search tree
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void treeSort(void** array, int len, int size, COMP_FUNC cmp);

#endif
