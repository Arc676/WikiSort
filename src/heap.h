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
	size_t count;
	int occupied;
	size_t size;
	COMP_FUNC* cmp;
} Heap;

/**
 * Create a new heap object
 * @param count Number of items to be stored in the heap
 * @param size Size of a single element
 * @param cmp Comparison function for the heap
 * @return A pointer to the newly created heap
 */
Heap* heap_create(size_t count, size_t size, COMP_FUNC cmp);

/**
 * Create a heap containing the objects in an array
 * @param array The array to heapify
 * @param count Number of objects in the array
 * @param size Size of a single element
 * @param cmp Comparison function for the heap
 * @return A pointer to the newly craeted heap
 */
Heap* heap_heapify(void** array, size_t count, size_t size, COMP_FUNC cmp);

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
 * Remove and return the maximum node in the heap
 * @param heap Heap from which to remove root
 * @return Pointer to a copy of the maximum node
 */
void** heap_pop(Heap* heap);

/**
 * Insert a new value into the heap
 * @param heap Heap into which to insert the value
 * @param val Value to insert
 */
void heap_insert(Heap* heap, void** value);

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
 * @param cmp Comparison function that returns if an element is smaller than another
 */
void heapSort(void** array, size_t len, size_t size, COMP_FUNC cmp);

#endif
