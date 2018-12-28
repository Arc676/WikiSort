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

void cartesianTreeSort(void** array, int len, int size, COMP_FUNC cmp, COMP_FUNC binTreeCmp) {
	BinaryTreeNode* cartesianTree = arrayToCartesianTree(array, len, size, cmp);
	Heap* queue = heap_create(pow(2, (int)log2(len)), sizeof(BinaryTreeNode), binTreeCmp);
	heap_push(queue, (void**)cartesianTree);
	void** ptr = array;
	for (int i = 0; i < len; i++) {
		BinaryTreeNode* next = (BinaryTreeNode*)heap_pop(queue);
		memcpy(ptr, next->value, size);
		if (next->leftChild) {
			heap_push(queue, (void**)next->leftChild);
		}
		if (next->rightChild) {
			heap_push(queue, (void**)next->rightChild);
		}
		free(next);
		ptr = adv(ptr, size);
	}
	heap_destroy(queue);
	destroyBinaryTree(cartesianTree);
}

int binTree_cmp_int(void** a, void** b) {
	BinaryTreeNode* na = (BinaryTreeNode*)a;
	BinaryTreeNode* nb = (BinaryTreeNode*)b;
	return -cmp_int(na->value, nb->value);
}
