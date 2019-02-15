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

#include "splay.h"

BinaryTreeNode* arrayToSplayTree(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* tree = createBinaryTreeNode(array, size, NULL, NULL, NULL);
	void** ptr = adv(array, size);
	for (int i = 1; i < len; i++) {
		BinaryTreeNode* node = binaryTree_insert(tree, ptr, cmp);
		splayTree_splay(node);
		tree = node;
		ptr = adv(ptr, size);
	}
	return tree;
}

void splayTree_splay(BinaryTreeNode* node) {
	while (node->parent) {
		int npos = binaryTree_nodePosition(node);
		int ppos = binaryTree_nodePosition(node->parent);
		if (!node->parent->parent) {
			if (npos == LNODE) {
				splayTree_rotate(node->parent, RNODE);
			} else {
				splayTree_rotate(node->parent, LNODE);
			}
		} else if (npos == LNODE && ppos == LNODE) {
			splayTree_rotate(node->parent->parent, RNODE);
			splayTree_rotate(node->parent, RNODE);
		} else if (npos == RNODE && ppos == RNODE) {
			splayTree_rotate(node->parent->parent, LNODE);
			splayTree_rotate(node->parent, LNODE);
		} else if (npos == LNODE && ppos == RNODE) {
			splayTree_rotate(node->parent, RNODE);
			splayTree_rotate(node->parent, LNODE);
		} else {
			splayTree_rotate(node->parent, LNODE);
			splayTree_rotate(node->parent, RNODE);
		}
	}
}

void splayTree_rotate(BinaryTreeNode* node, int dir) {
	BinaryTreeNode* child = dir == LNODE ? node->rightChild : node->leftChild;
	if (child) {
		if (dir == LNODE) {
			node->rightChild = child->leftChild;
			if (child->leftChild) {
				child->leftChild->parent = node;
			}
			child->leftChild = node;
		} else {
			node->leftChild = child->rightChild;
			if (child->rightChild) {
				child->rightChild->parent = node;
			}
			child->rightChild = node;
		}
		child->parent = node->parent;
	}
	if (node->parent) {
		if (binaryTree_nodePosition(node) == LNODE) {
			node->parent->leftChild = child;
		} else {
			node->parent->rightChild = child;
		}
	}
	node->parent = child;
}

BinaryTreeNode* splayTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp) {
	BinaryTreeNode* new = binaryTree_insert(root, value, cmp);
	splayTree_splay(new);
	return new;
}

void splayTree_delete(BinaryTreeNode* node) {
	BinaryTreeNode* parent = node->parent;
	binaryTree_delete(node);
	if (parent) {
		splayTree_splay(parent);
	}
}

BinaryTreeNode* splayTree_find(BinaryTreeNode* root, void** value, COMP_FUNC cmp) {
	BinaryTreeNode* found = binaryTree_find(root, value, cmp);
	if (found) {
		splayTree_splay(found);
	}
	return found;
}

void splaySort(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* splayTree = arrayToSplayTree(array, len, size, cmp);
	traverse(splayTree, array, IN_ORDER, LTOR);
	destroyBinaryTree(splayTree);
}
