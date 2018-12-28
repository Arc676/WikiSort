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

#include "tree.h"

int inOrderTraversal(BinaryTreeNode* root, void** dst) {
	if (!root) {
		return 0;
	}
	int spaces = inOrderTraversal(root->leftChild, dst);
	dst = adv(dst, spaces * root->size);

	memcpy(dst, root->value, root->size);
	dst = adv(dst, root->size);

	return spaces + 1 + inOrderTraversal(root->rightChild, dst);
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

void binaryTree_insert(BinaryTreeNode* root, void** value, COMP_FUNC cmp) {
	int res = cmp(root->value, value);
	BinaryTreeNode* nextNode = res == -1 ? root->rightChild : root->leftChild;
	if (nextNode) {
		binaryTree_insert(nextNode, value, cmp);
	} else {
		BinaryTreeNode* new = createBinaryTreeNode(value, root->size, root, NULL, NULL);
		if (res == -1) {
			root->rightChild = new;
		} else {
			root->leftChild = new;
		}
	}
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
	inOrderTraversal(tree, array);
	destroyBinaryTree(tree);
}
