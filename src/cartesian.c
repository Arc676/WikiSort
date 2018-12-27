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

#include "cartesian.h"

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

BinaryTreeNode* arrayToCartesianTree(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* tree = createBinaryTreeNode(array, size, NULL, NULL, NULL);
	BinaryTreeNode* lastProcessed = tree;
	void** ptr = adv(array, size);
	for (int i = 1; i < len; i++) {
		while (1) {
			if (cmp(lastProcessed->value, ptr) == -1) {
				BinaryTreeNode* rChild = lastProcessed->rightChild;
				BinaryTreeNode* next = createBinaryTreeNode(ptr, size, lastProcessed, rChild, NULL);
				lastProcessed->rightChild = next;
				lastProcessed = next;
				break;
			} else {
				if (lastProcessed->parent) {
					lastProcessed = lastProcessed->parent;
				} else {
					BinaryTreeNode* next = createBinaryTreeNode(ptr, size, NULL, lastProcessed, NULL);
					tree = next;
					lastProcessed = next;
					break;
				}
			}
		}
		ptr = adv(ptr, size);
	}
	return tree;
}

void cartesianTreeSort(void** array, int len, int size, COMP_FUNC cmp) {
	BinaryTreeNode* cartesianTree = createBinaryTreeNode(array, size, NULL, NULL, NULL);
	Heap* queue = heap_create(len, size, cmp); // the maximum size of the heap is probably something like len/2 + 1
	// add children of popped value to queue
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		void** next = heap_pop(queue);
		memcpy(ptr, next, size);
		free(next);
		ptr = adv(ptr, size);
	}
}
