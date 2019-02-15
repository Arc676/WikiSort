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

#include "tree.h"

int traverse(BinaryTreeNode* root, void** dst, int mode, int dir) {
	if (!root) {
		return 0;
	}
	BinaryTreeNode* child1 = dir == LTOR ? root->leftChild : root->rightChild;
	BinaryTreeNode* child2 = dir == LTOR ? root->rightChild : root->leftChild;
	int nodes = 0;

	// traverse a child node if required by traversal mode
	switch (mode) {
	case PRE_ORDER:
		break;
	case IN_ORDER:
	case POST_ORDER:
	{
		int spaces = traverse(child1, dst, mode, dir);
		dst = adv(dst, spaces * root->size);
		nodes += spaces;
		if (mode == POST_ORDER) {
			spaces = traverse(child2, dst, mode, dir);
			dst = adv(dst, spaces * root->size);
			nodes += spaces;
		}
		break;
	}
	}

	// copy the value at the given node
	memcpy(dst, root->value, root->size);
	dst = adv(dst, root->size);
	nodes++;

	// traverse a child node if required by traversal mode
	switch (mode) {
	case PRE_ORDER:
	{
		int spaces = traverse(child1, dst, mode, dir);
		dst = adv(dst, spaces * root->size);
		nodes += spaces;
	}
	case IN_ORDER:
		nodes += traverse(child2, dst, mode, dir);
		break;
	case POST_ORDER:
		break;
	}

	return nodes;
}

int binaryTree_size(BinaryTreeNode* root) {
	if (!root) {
		return 0;
	}
	return binaryTree_size(root->leftChild) + binaryTree_size(root->rightChild) + 1;
}

BinaryTreeNode* arrayToBinaryTree(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* tree = createBinaryTreeNode(array, size, NULL, NULL, NULL);
	void** ptr = adv(array, size);
	for (int i = 1; i < len; i++) {
		binaryTree_insert(tree, ptr, cmp);
		ptr = adv(ptr, size);
	}
	return tree;
}

BinaryTreeNode* binaryTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp) {
	int res = cmp(root->value, value);
	BinaryTreeNode* nextNode = res == -1 ? root->rightChild : root->leftChild;
	if (nextNode) {
		return binaryTree_insert(nextNode, value, cmp);
	} else {
		BinaryTreeNode* new = createBinaryTreeNode(value, root->size, root, NULL, NULL);
		if (res == -1) {
			root->rightChild = new;
		} else {
			root->leftChild = new;
		}
		return new;
	}
}

void binaryTree_delete(BinaryTreeNode* node) {
	if (!node) {
		return;
	}
	// prepare for deletion
	BinaryTreeNode* parent = node->parent;
	BinaryTreeNode* replacement = NULL;

	// check for child node presence
	if (node->leftChild && node->rightChild) {
		replacement = binaryTree_findMin(node->rightChild);
		memcpy(node->value, replacement->value, node->size);
		binaryTree_delete(replacement);
		return;
	} else if (node->leftChild) {
		replacement = node->leftChild;
	} else if (node->rightChild) {
		replacement = node->rightChild;
	}

	// update parent node for moved node, if needed
	if (replacement) {
		replacement->parent = parent;
	}

	// update child reference for parent node
	if (binaryTree_nodePosition(node) == LNODE) {
		parent->leftChild = replacement;
	} else if (parent) {
		parent->rightChild = replacement;
	}

	// destroy node
	free(node->value);
	free(node);
}

BinaryTreeNode* binaryTree_find(BinaryTreeNode* root, void** value, COMP_FUNC cmp) {
	if (!root) {
		return NULL;
	}
	switch (cmp(root->value, value)) {
	case -1:
		return binaryTree_find(root->rightChild, value, cmp);
	case 1:
		return binaryTree_find(root->leftChild, value, cmp);
	case 0:
	default:
		return root;
	}
}

BinaryTreeNode* binaryTree_findMin(BinaryTreeNode* root) {
	while (root->leftChild) {
		root = root->leftChild;
	}
	return root;
}

int binaryTree_nodePosition(BinaryTreeNode* node) {
	BinaryTreeNode* parent = node->parent;
	if (parent) {
		if (parent->leftChild == node) {
			return LNODE;
		}
		return RNODE;
	}
	return ROOT;
}

BinaryTreeNode* createBinaryTreeNode(void** value, int size, BinaryTreeNode* parent, BinaryTreeNode* left, BinaryTreeNode* right) {
	BinaryTreeNode* node = malloc(sizeof(BinaryTreeNode));
	node->value = malloc(size);
	memcpy(node->value, value, size);
	node->size = size;
	node->parent = parent;
	node->leftChild = left;
	node->rightChild = right;
	return node;
}

void destroyBinaryTree(BinaryTreeNode* root) {
	if (!root) {
		return;
	}
	destroyBinaryTree(root->leftChild);
	destroyBinaryTree(root->rightChild);
	free(root->value);
	free(root);
}

void treeSort(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* tree = arrayToBinaryTree(array, len, size, cmp);
	traverse(tree, array, IN_ORDER, LTOR);
	destroyBinaryTree(tree);
}
