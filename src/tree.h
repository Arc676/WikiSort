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

// Tree traversal order
#define PRE_ORDER  0
#define IN_ORDER   1
#define POST_ORDER 2

// Tree traversal direction
#define LTOR 0
#define RTOL 1

// Node position type
#define ROOT  0
#define LNODE 1
#define RNODE 2

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
 * through a traversal of the tree
 * @param root Root node of the tree to traverse
 * @param dst Destination for the tree's contents
 * @param mode Traversal order
 * @param dir Traversal direction
 * @return Number of nodes traversed
 */
int traverse(BinaryTreeNode* root, void** dst, int mode, int dir);

/**
 * Determines the number of nodes in a binary tree
 * @param root Node from which to start counting
 * @return Number of nodes in the given tree
 */
int binaryTree_size(BinaryTreeNode* root);

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
 * @return The newly inserted node
 */
BinaryTreeNode* binaryTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp);

/**
 * Removes a node from a binary tree
 * @param node Node to remove
 */
void binaryTree_delete(BinaryTreeNode* node);

/**
 * Finds a value in a binary tree
 * @param root Node from which to start searching
 * @param value The value to search for
 * @param cmp Element comparison function
 * @return Node containing the searched-for value, or NULL if no such node was found
 */
BinaryTreeNode* binaryTree_find(BinaryTreeNode* root, void** value, COMP_FUNC cmp);

/**
 * Finds the minimum value in a binary tree
 * @param root Node from which to start searching
 * @return The node containing the minimum value in the tree rooted at the given node
 */
BinaryTreeNode* binaryTree_findMin(BinaryTreeNode* root);

/**
 * Determine what kind of position is occupied by a node in its tree
 * @param node Node to check
 * @return Whether the node is a root node, left child, or right child
 */
int binaryTree_nodePosition(BinaryTreeNode* node);

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
