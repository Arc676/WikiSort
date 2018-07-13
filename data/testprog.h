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

// ******

// This header and corresponding C file declare and define methods that encapsulate
// actions taken to analyze sorting algorithms and output the gathered data
// to a file, as well as macros that can be used to alter the parameters of the test

// You can define the following macros during compilation to customize the test

// Maximum array length
#ifndef MAX_LEN
#define MAX_LEN 600
#endif

// Starting array length
#ifndef START_LEN
#define START_LEN 100
#endif

// Array length increment
#ifndef LEN_INC
#define LEN_INC 100
#endif

// If set to 1, array length increases by LEN_INC each time. If set to a falsy
// value, array length is scaled up by LEN_INC each time instead. Defaults to 1.
#ifndef LIN_GROWTH
#define LIN_GROWTH 1
#endif

// Number of trials to perform for each array length
#ifndef NUM_TRIALS
#define NUM_TRIALS 10
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

/**
 * Common initialization code for test programs; handles argument validation
 * and prints first row to output file
 * @param argc Number of command line arguments passed
 * @param argv Command line arguments
 * @param progName Name of program
 * @param independents Number of independent variable values (e.g. sorting algorithms)
 * @param ... Variadic list of independent variable values
 * @return Output file if initialization successful, NULL otherwise
 */
FILE* initialize(int argc, char* argv[], char* progName, int independents, ...);
