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

// WikiSort sample program
// Points
// Input: a set of points represented with their X,Y coordinates
// Output: the list of points sorted by their Euclidean distance from the origin

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "merge.h"

struct Point {
	double x;
	double y;
};

double norm2(struct Point p) {
	return sqrt(p.x * p.x + p.y * p.y);
}

int cmp_dist(void** a, void** b) {
	struct Point A = *(struct Point*)a;
	struct Point B = *(struct Point*)b;
	double na = norm2(A);
	double nb = norm2(B);
	return cmp_double((void**)&na, (void**)&nb);
}

int main(int argc, char* argv[]) {
	if (argc % 2 == 0 || argc == 1) {
		fprintf(stderr, "Usage: points x1 y1 [x2 y2 ...]\n");
		return 1;
	}
	int len = (argc - 1) / 2;
	struct Point* arr = malloc(len * sizeof(struct Point));
	for (int i = 0, arg = 1; i < len; i++, arg += 2) {
		arr[i] = (struct Point){
			atoi(argv[arg]), atoi(argv[arg + 1])
		};
	}
	printf("Input:  ");
	for (int i = 0; i < len; i++) {
		printf("(%f,%f) ", arr[i].x, arr[i].y);
	}
	printf("\n");
	mergeSort((void**)arr, len, sizeof(struct Point), cmp_dist);
	printf("Output: ");
	for (int i = 0; i < len; i++) {
		printf("(%f,%f) ", arr[i].x, arr[i].y);
	}
	printf("\n");
	if (isSorted((void**)arr, len, sizeof(struct Point), cmp_dist)) {
		printf("List sorted!\n");
		return 0;
	}
	fprintf(stderr, "Failed to sort list\n");
	return 1;
}
