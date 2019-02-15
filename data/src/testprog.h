//Copyright (C) 2018-9 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

// ******

// This header and corresponding C file declare and define methods that encapsulate
// actions taken to analyze sorting algorithms and output the gathered data
// to a file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/resource.h>

typedef struct timeval TIME;

int MAX_LEN, START_LEN, LEN_INC, LIN_GROWTH, NUM_TRIALS, BOUND;

/**
 * Typedef for generation functions; should generate data for arrays so
 * tests can be run
 * @param arrlen Length of array
 */
typedef void GEN_FUNC(int arrlen);

/**
 * Typedef for test functions; should run the test assuming the array
 * is of the given length and return the runtime
 * @param arrlen Array length
 * @return Test runtime in microseconds
 */
typedef unsigned long TEST_FUNC(int arrlen);

/**
 * Common initialization code for test programs; parses command line arguments
 * and prints first row to output file
 * @param argc Number of command line arguments passed
 * @param argv Command line arguments
 * @param progName Name of program
 * @param independents Number of independent variable values (e.g. sorting algorithms)
 * @param ... Variadic list of independent variable values
 * @return Output file if initialization successful, NULL otherwise
 */
FILE* initialize(int argc, char* argv[], char* progName, int independents, ...);

/**
 * Creates a 2D array for storing data with the given number of rows
 * @param rows Number of independent variable values
 * @return A rows by NUM_TRIALS array of unsigned longs
 */
unsigned long** makeData(int rows);

/**
 * Frees the memory allocated to a 2D data array
 * @param data Table to free
 * @param rows Nunmber of independent variable values
 */
void destroyData(unsigned long** data, int rows);

void getClock(TIME* timeval);

unsigned long getDelta(TIME* start, TIME* end);

/**
 * Runs the tests and records the results
 * @param output File to which to write results
 * @param generate Function that generates data for each trial
 * @param tests Array of functions that run the tests
 * @param independent Number of independent variable values (or function pointers)
 * @param data 2D array in which to store data
 */
void runTests(FILE* output, GEN_FUNC generate, TEST_FUNC* tests[],
	int independents, unsigned long** data);
