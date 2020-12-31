//Copyright (C) 2018-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "heap.h"

Heap* heap_create(int count, int size, COMP_FUNC cmp) {
	Heap* heap = malloc(sizeof(Heap));
	heap->elements = malloc(count * size);
	heap->count = count;
	heap->occupied = 0;
	heap->size = size;
	heap->cmp = cmp;
	return heap;
}

Heap* heap_heapify(void** array, int count, int size, COMP_FUNC cmp) {
	Heap* heap = heap_create(count, size, cmp);
	void** new = array;
	for (int i = 0; i < count; i++) {
		heap_push(heap, new);
		new = adv(new, size);
	}
	return heap;
}

Heap* heap_merge(Heap* heap1, Heap* heap2) {
	if (heap1->size != heap2->size || heap1->cmp != heap2->cmp) {
		return 0;
	}
	int total = heap1->count + heap2->count;
	void** elements = malloc(total * heap1->size);
	memcpy(elements, heap1->elements, heap1->occupied * heap1->size);

	void** right = adv(elements, heap1->occupied * heap1->size);
	memcpy(right, heap2->elements, heap2->occupied * heap2->size);

	return heap_heapify(elements, total, heap1->size, heap1->cmp);
}

void heap_meld(Heap* heap1, Heap* heap2) {
	Heap* new = heap_merge(heap1, heap2);
	if (new) {
		heap_destroy(heap1);
		heap_destroy(heap2);
		*heap1 = *new;
	}
}

void heap_resize(Heap* heap, int size) {
	if (heap->count == size || heap->occupied > size) {
		return;
	}
	void** new = realloc(heap->elements, size * heap->size);
	if (new) {
		heap->count = size;
		heap->elements = new;
	} else {
		perror("Failed to allocate memory");
	}
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

void heap_push(Heap* heap, void** value) {
	// if heap is full, double capacity
	if (heap->occupied == heap->count) {
		heap_resize(heap, heap->count * 2);
	}

	// copy new value into heap
	void** dst = adv(heap->elements, heap->occupied * heap->size);
	memcpy(dst, value, heap->size);

	// sift up
	heap_siftUp(heap, heap->occupied);

	// increase heap node count
	heap->occupied++;
}

void** heap_pop(Heap* heap) {
	// if heap is empty, return null
	if (!heap->occupied) {
		return 0;
	}

	// copy max node
	void** max = malloc(heap->size);
	memcpy(max, heap->elements, heap->size);

	// delete root
	heap_delete(heap, 0);

	// return max node
	return max;
}


void heap_replace(Heap* heap, void** value) {
	memcpy(heap->elements, value, heap->size);
	heap_siftDown(heap, 0);
}

void heap_delete(Heap* heap, int index) {
	if (index >= heap->occupied) {
		return;
	}
	void** end = adv(heap->elements, (heap->occupied - 1) * heap->size);
	void** toDelete = adv(heap->elements, index * heap->size);
	swapElements(toDelete, end, heap->size);
	heap->occupied--;
	heap_siftDown(heap, index);
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

void heapSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	Heap* heap = heap_heapify(array, len, size, cmp);
	void** dst = adv(array, (len - 1) * size);
	for (int i = len - 1; i >= 0; i--) {
		void** obj = heap_pop(heap);
		memcpy(dst, obj, size);
		free(obj);

		#ifdef VISUALIZER
		visualizer_updateArray(dst, 1, size);

		if (visualizer_abortRequested()) {
			break;
		}
		#endif

		dst = adv(dst, -size);
	}
	heap_destroy(heap);
}
