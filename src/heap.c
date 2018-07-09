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

#include "heap.h"

Heap* heap_create(size_t count, size_t size, COMP_FUNC cmp) {
	Heap* heap = malloc(sizeof(Heap));
	heap->elements = malloc(count * size);
	heap->count = count;
	heap->occupied = 0;
	heap->size = size;
	heap->cmp = cmp;
	return heap;
}

Heap* heap_heapify(void** array, size_t count, size_t size, COMP_FUNC cmp) {
	Heap* heap = heap_create(count, size, cmp);
	for (int i = 0; i < count; i++) {
		void** new = adv(array, i * size);
		heap_insert(heap, new);
	}
	return heap;
}

void heap_destroy(Heap* heap) {
	free(heap->elements);
	free(heap);
}

int heap_getParent(int index) {
	return (index - 1) / 2;
}

int heap_getChild(int index, int child) {
	return index * 2 + child;
}

void** heap_peek(Heap* heap) {
	return heap->elements;
}

void** heap_pop(Heap* heap) {
	// if heap is empty, return null
	if (!heap->occupied) {
		return 0;
	}

	// copy max node
	void** max = malloc(heap->size);
	memcpy(max, heap->elements, heap->size);

	// swap root with bottom node and sift down
	void** end = adv(heap->elements, (heap->occupied - 1) * heap->size);
	swapElements(heap->elements, end, heap->size);
	heap->occupied--;
	heap_siftDown(heap, 0);

	// return max node
	return max;
}

void heap_insert(Heap* heap, void** value) {
	// if heap is full, allocate new layer of memory
	if (heap->occupied == heap->count) {
		size_t expanded = heap->count * 2;
		void** new = realloc(heap->elements, expanded * heap->size);
		if (new) {
			heap->count = expanded;
			heap->elements = new;
		} else {
			perror("Failed to allocate memory");
		}
	}

	// insert new value in heap
	void** dst = adv(heap->elements, heap->occupied * heap->size);
	memcpy(dst, value, heap->size);

	// sift up
	heap_siftUp(heap, heap->occupied);

	// increase heap node count
	heap->occupied++;
}

void heap_siftUp(Heap* heap, int index) {
	while (1) {
		int parentIndex = heap_getParent(index);
		void** parentNode = adv(heap->elements, parentIndex * heap->size);
		void** node = adv(heap->elements, index * heap->size);
		if (heap->cmp(node, parentNode) == 1) {
			swapElements(node, parentNode, heap->size);
			index = parentIndex;
		} else {
			break;
		}
	}
}

void heap_siftDown(Heap* heap, int index) {
	while (1) {
		int lIdx = heap_getChild(index, CHILD_LEFT);
		int rIdx = heap_getChild(index, CHILD_RIGHT);

		void** lChild = 0;
		void** rChild = 0;

		if (lIdx < heap->occupied) {
			lChild = adv(heap->elements, lIdx * heap->size);
		}
		if (rIdx < heap->occupied) {
			rChild = adv(heap->elements, rIdx * heap->size);
		}

		void** node = adv(heap->elements, index * heap->size);

		int largestIdx = index;
		void** largest = node;

		if (lChild && heap->cmp(lChild, largest) == 1) {
			largestIdx = lIdx;
			largest = lChild;
		}
		if (rChild && heap->cmp(rChild, largest) == 1) {
			largestIdx = rIdx;
			largest = rChild;
		}

		if (largestIdx == index) {
			break;
		} else {
			index = largestIdx;
			swapElements(node, largest, heap->size);
		}
	}
}

void heapSort(void** array, size_t len, size_t size, COMP_FUNC cmp) {
	Heap* heap = heap_heapify(array, len, size, cmp);
	for (int i = len - 1; i >= 0; i--) {
		void** obj = heap_pop(heap);
		void** dst = adv(array, i * size);
		memcpy(dst, obj, size);
	}
	heap_destroy(heap);
}

