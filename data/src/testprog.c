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

#include "testprog.h"

int MAX_LEN = 1000, START_LEN = 100, LEN_INC = 100, LIN_GROWTH = 1, NUM_TRIALS = 10, BOUND = 100;

FILE* initialize(int argc, char* argv[], char* progName, int independents, ...) {
	int flag;
	FILE* output = NULL;
	while ((flag = getopt(argc, argv, "m:s:i:et:o:b:")) != -1) {
		switch (flag) {
			case 'm':
				MAX_LEN = atoi(optarg);
				break;
			case 's':
				START_LEN = atoi(optarg);
				break;
			case 'i':
				LEN_INC = atoi(optarg);
				break;
			case 'e':
				LIN_GROWTH = 0;
				break;
			case 't':
				NUM_TRIALS = atoi(optarg);
				break;
			case 'o':
				if (output) {
					fprintf(stderr, "Cannot specify more than one output file\n");
					return NULL;
				}
				output = fopen(optarg, "w");
				break;
			case 'b':
				BOUND = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Unknown flag: %c\n", flag);
				return NULL;
		}
	}
	if (!output) {
		fprintf(stderr, "Failed to open output file or none given\n");
		return NULL;
	}
	srand(time(NULL));
	fprintf(output, "Length,");
	va_list IVs;
	va_start(IVs, independents);
	for (int iv = 0; iv < independents; iv++) {
		char* name = va_arg(IVs, char*);
		for (int i = 0; i < NUM_TRIALS; i++) {
			fprintf(output, "%s %d,", name, i + 1);
		}
		fprintf(output, "%s AVG,", name);
	}
	va_end(IVs);
	fprintf(output, "\n");
	return output;
}

unsigned long** makeData(int rows) {
	unsigned long** data = malloc(rows * sizeof(unsigned long*));
	for (int i = 0; i < rows; i++) {
		data[i] = malloc(NUM_TRIALS * sizeof(unsigned long));
	}
	return data;
}

void destroyData(unsigned long** data, int rows) {
	for (int i = 0; i < rows; i++) {
		free(data[i]);
	}
	free(data);
}

void getClock(TIME* timeval) {
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	*timeval = usage.ru_utime;
}

unsigned long getDelta(TIME* start, TIME* end) {
	return 1e6 * (end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec);
}

void runTests(FILE* output, GEN_FUNC generate, TEST_FUNC* tests[],
	int independents, unsigned long** data) {
	for (int arrlen = START_LEN; arrlen <= MAX_LEN;) {
		printf("\r\tSorting arrays of length %d...", arrlen);
		fflush(stdout);
		fprintf(output, "%d,", arrlen);
		for (int trial = 0; trial < NUM_TRIALS; trial++) {
			generate(arrlen);
			for (int sort = 0; sort < independents; sort++) {
				data[sort][trial] = tests[sort](arrlen);
			}
		}
		for (int sort = 0; sort < independents; sort++) {
			long double total = 0;
			for (int trial = 0; trial < NUM_TRIALS; trial++) {
				total += data[sort][trial];
				fprintf(output, "%lu,", data[sort][trial]);
			}
			fprintf(output, "%Lf,", total / NUM_TRIALS);
		}
		fprintf(output, "\n");
		if (LIN_GROWTH) {
			arrlen += LEN_INC;
		} else {
			arrlen *= LEN_INC;
		}
	}
	printf("\nProgram terminated\n");
	fclose(output);
}
