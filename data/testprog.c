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

FILE* initialize(int argc, char* argv[], char* progName, int independents, ...) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s outputFile.csv\n", progName);
		return NULL;
	}
	srand(time(NULL));
	FILE* output = fopen(argv[1], "w");
	if (!output) {
		fprintf(stderr, "Failed to open output file\n");
		return NULL;
	}
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
