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

#ifndef SHELL_H
#define SHELL_H

#include "wikisort.h"

typedef enum GapSequence {
	Shell_1959,
	Frank_Lazarus_1960,
	A168604,
	A083318,
	A003586,
	A003462,
	A036569,
	A036562,
	A033622,
	Gonnet_BaezaYates_1991,
	A108870,
	A102549,
	GAP_COUNT
} GapSequence;

const int ciuraSequence[8];

/**
 * Typedef for gap sequence generating functions
 * @param len Length of array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing gap sequence
 */
typedef int* GAP_GEN(int len, int* count);

GAP_GEN *gapSeqs[GAP_COUNT];

/**
 * Sorts the given array using a shellsort algorithm
 * @param array The array to sort
 * @param len The length of the array
 * @param size The size of a single element
 * @param cmp Element comparison function
 * @param seq Desired gap sequence
 */
void shellSort(void** array, int len, int size, COMP_FUNC cmp, GapSequence seq);

/**
 * Generate a gap sequence formed by using a shrink factor on the size
 * of the input
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @param shrink Desired shrink factor
 * @return Pointer to array containing the gap sequence
 */
int* gShrinkFactor(int len, int* count, float shrink);

/**
 * Generate the gap sequence described by Shell in 1959;
 * worst time complexity Θ(N^2); given by floor(N/2^k)
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gShell(int len, int* count);

/**
 * Generate the gap sequence described by Frank and
 * Lazarus in 1960; worst time complexity Θ(N^3/2);
 * given by 2*floor(N/2^k+1)+1
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gFrank_Lazarus(int len, int* count);

/**
 * Generate the gap sequence described by Hibbard in
 * 1963; worst time complexity Θ(N^3/2); given by 2^k - 1
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA168604(int len, int* count);

/**
 * Generate the gap sequence described by Papernov and
 * Stasevich in 1965; worst time complexity Θ(N^3/2);
 * given by 2^k + 1, prefixed by 1
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA083318(int len, int* count);

/**
 * Generate the gap sequence described by Pratt in 1971;
 * worst time complexity Θ(Nlog^2N); given by successive
 * terms of the form 2^p * 3^q
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA003586(int len, int* count);

/**
 * Generate the gap sequence described by Pratt in 1971;
 * worst time complexity Θ(N^3/2); given by (3^k - 1)/2
 * not greater than ceil(N/3)
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA003462(int len, int* count);

/**
 * Returns the greatest common divisor (or factor) of two numbers
 * @param a First number
 * @param b Second number
 * @return GCD/GCF of the numbers
 */
int gcd(int a, int b);

/**
 * Generates the terms of the sequence A036567 on the OEIS
 * where the Nth term exceeds 2.5^n and is relatively coprime
 * with all the other terms i.e. gcd(a_n, A) = 1 for all A in the sequence
 * except for a_n
 * @param len Number of terms of the sequence to generate
 * @return Newly allocated list containing the sequence
 */
int* gA036567(int len);

/**
 * Generate the gap sequence described by Incerpi and
 * Sedgewick described in 1985 as well as Knuth; see
 * the Wikipedia page for time complexity and general term
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA036569(int len, int* count);

/**
 * Generate the gap sequence described by Sedgewick in
 * 1986; worst time complexity O(N^4/3); given by
 * 4^k + 3*2^k-1 + 1, prefixed with 1
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA036562(int len, int* count);

/**
 * Generate the gap sequence described by Sedgewick in
 * 1986; worst time complexity O(N^4/3); given by
 * 9*(2^k - 2^k/2) + 1 for even k, 8*2^k - 6*2^(k+1)/2 + 1
 * for odd k
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA033622(int len, int* count);

/**
 * Generate the gap sequence described by Gonnet and
 * Baeza-Yates in 1991; worst time complexity unknown;
 * given by h_k = max(1, floor(5*h_k-1/11)) starting with
 * h_0 = N
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gGonnet_BaezaYates(int len, int* count);

/**
 * Generate the gap sequence described by Tokuda in 1992;
 * worst time complexity unknown; given by ceil((9*(9/4)^k-1 - 4)/5)
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA108870(int len, int* count);

/**
 * Generate the gap sequence described by Ciura in 2001;
 * worst time complexity unknown; terms determined experimentally
 * @param len Length of the array
 * @param count Pointer to integer in which to store number of gaps generated
 * @return Pointer to array containing the gap sequence
 */
int* gA102549(int len, int* count);

#endif
