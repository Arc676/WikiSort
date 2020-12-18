//Copyright (C) 2018-20 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HEAP_H
#define HEAP_H

#define CHILD_LEFT 1
#define CHILD_RIGHT 2

#include <stdio.h>

#include "wikisort.h"

/**
 * Binary heap data structure, implemented as an array with the maximum item
 * at the root
 */
typedef struct Heap {
	void** elements;
	int count;
	int occupied;
	int size;
	COMP_FUNC* cmp;
} Heap;

/**
 * Create a new heap object
 * @param count Number of items to be stored in the heap
 * @param size Size of a single element
 * @param cmp Element comparison function
 * @return A pointer to the newly created heap
 */
Heap* heap_create(int count, int size, COMP_FUNC cmp);

/**
 * Create a heap containing the objects in an array
 * @param array The array to heapify
 * @param count Number of objects in the array
 * @param size Size of a single element
 * @param cmp Element comparison function
 * @return A pointer to the newly craeted heap
 */
Heap* heap_heapify(void** array, int count, int size, COMP_FUNC cmp);

/**
 * Merge the contents of two heaps into one new heap (returns null if
 * heaps do not have the same element size or comparison function)
 * @param heap1 First heap
 * @param heap2 Second heap
 * @return A pointer to the new heap containing the elements of both
 */
Heap* heap_merge(Heap* heap1, Heap* heap2);

/**
 * Meld the contents of two heaps into the first heap and destroy the second
 * @param heap1 First (destination) heap
 * @param heap2 Second (to be destroyed) heap
 */
void heap_meld(Heap* heap1, Heap* heap2);

/**
 * Change the amount of memory allocated to a given heap (does nothing if
 * the new size is equal to the current size or if the new size is insufficient
 * to store the heap's current contents)
 * @param heap Heap to resize
 * @param size New size
 */
void heap_resize(Heap* heap, int size);

/**
 * Destroy a heap
 * @param heap Heap to destroy
 */
void heap_destroy(Heap* heap);

/**
 * Get the index of the parent of the node
 * with a given index in a heap
 * @param index Index of node
 * @return Index of that node's parent
 */
int heap_getParent(int index);

/**
 * Get the index of a child of the node
 * with a given index in a heap
 * @param index Index of node
 * @param child Child whose index to obtain
 * @return Index of the desired child node
 */
int heap_getChild(int index, int child);

/**
 * Determine the value of the maximum node in the heap
 * @param heap Heap to check
 * @return Pointer to the maximum node
 */
void** heap_peek(Heap* heap);

/**
 * Insert a new value into the heap
 * @param heap Heap into which to insert the value
 * @param value Value to insert
 */
void heap_push(Heap* heap, void** value);

/**
 * Remove and return the maximum node in the heap
 * @param heap Heap from which to remove root
 * @return Pointer to a copy of the maximum node (NULL if heap is empty)
 */
void** heap_pop(Heap* heap);

/**
 * Replaces the value at the root of the heap
 * @param heap Heap whose root to replace
 * @param value Value to put in current root's place
 */
void heap_replace(Heap* heap, void** value);

/**
 * Deletes a node from the heap (does nothing if the index is greater than that
 * of the last element in the heap)
 * @param heap Heap from which to delete node
 * @param index Index of node to delete
 */
void heap_delete(Heap* heap, int index);

/**
 * Sifts a node up the heap to its correct position
 * @param heap Heap in which the node is found
 * @param index Index of node to sift up
 */
void heap_siftUp(Heap* heap, int index);

/**
 * Sifts a node down the heap to its correct position
 * @param heap Heap in which the node is found
 * @param index Index of node to sift down
 */
void heap_siftDown(Heap* heap, int index);

/**
 * Sorts the given array using a heapsort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 */
void heapSort(void** array, int len, int size, COMP_FUNC cmp);

#endif

#ifdef __cplusplus
}
#endif
