#ifndef SORT_H

#define SORT_H 1

/** \file /SortingAlg/sort.h
 * \brief A file that holds sorting algorithms and comparators
 */

#define $$$ printf ("line %d\n",  __LINE__);

#include <stdio.h>
#include <stdlib.h>
#include "myAssert/myAssert.h"
#include <cstring>

typedef unsigned char uc;
const double stdError = 1e-10;

/**
 * \brief A function that swaps two variables byte-by-byte
 * \param[in, out] void *a          - pointer to the first  variable casted to void
 * \param[in, out] void *b          - pointer to the second variable casted to void
 * \param[in]  size_t size      - size of the type of the variables
 **/
inline void swap (void *a, void *b, size_t size);

/**
 * \brief A function that dumps an array of integer values in a special format 
 * \param[in] const char *tag        - pointer to the string which will be printed out before dumping
 * \param[in] const char *ptr        - pointer to the array which will be dumped
 * \param[in] int left               - the first element to be dumped
 * \param[in] int right              - the last element to be dumped   
 **/
void dump_list(const char *tag, int *ptr, int left, int right);

/**
 * \brief A service function that runs the exchange part of quicksortMy algorithm 
 * \param[in, out] void *array - a pointer to the array which is being sorted by qsort
 * \param[in] size_t left - the place of the first element in the array to be sorted
 * \param[in] size_t end  - the place of the last element in the array to be sorted
 * \param[in] int (*comparator) (const void*, const void*) - comparator func with certain format
 **/
size_t partition(void *array, size_t left, size_t right, size_t elementSize, int (*comparator) (const void*, const void*));

/**
 * \brief A service function that runs the reqursion part of quicksortMy algorithm 
 * \param[in, out] void *array - a pointer to the array which is being sorted by qsort
 * \param[in] size_t left - the place of the first element in the array to be sorted
 * \param[in] size_t end  - the place of the last element in the array to be sorted
 * \param[in] int (*comparator) (const void*, const void*) - comparator func with certain format
 **/
void quicksort(void *array, size_t start, size_t end, size_t elementSize, int (*comparator) (const void*, const void*));

/**
 * \brief A wrap for quicksort function for it to have the same signature as standard qsort
 * \param[in, out] void *array - a pointer to the array which is being sorted by qsort
 * \param[in] size_t nmemb - number of elements to be sorted
 * \param[in] size_t elementSize  - the size of a single element in the array
 * \param[in] int (*comparator) (const void*, const void*) - comparator func with certain format
 **/
void qsortMy (void *array, size_t nmemb, size_t elementSize, int (*comparator) (const void*, const void*));

/**
 * \brief A function that checks if the array of integers is sorted from lowest to highest
 * \param[in, out] int *array - pointer to the first element of the array to be checked
 * \param[in] size_t arraySize - size of the array to be sorted
 **/
bool isSortedInt (int *array, size_t arraySize);

/**
 * \brief A functions that is a comparator used in qsort for integers
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareInt (const void* n1, const void* n2);

/**
 * \brief A functions that is a comparator used in qsort for doubles
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareDouble (const void* n1, const void* n2);

/**
 * \brief A functions that is a comparator used in qsort for integers
 * (reversed from higher to lower)
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareIntReverse (const void* n1, const void* n2);

/**
 * \brief A functions that is a comparator used in qsort for Line struct (alphabetical)
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareLineStruct (const void* n1, const void* n2);

/**
 * \brief A functions that is a comparator used in qsort for Line struct (from the ends)
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareLineStructEnd (const void* n1, const void* n2);

/**
 * \brief A functions that is a comparator used in qsort for char pointer arrays (alphabetical)
 * \param[in] const void* n1 - First value to compare
 * \param[in] const void* n2 - Second value to compare
 **/
int compareStr (const void* v1, const void* v2);

#endif
