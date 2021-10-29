/**
 * \file strlibMy.h
 *
 * \brief A file that consists of functions to work with strings
 **/

#pragma once

#define $$$ printf ("line %d\n",  __LINE__);

#define DEBUG_SOFT

#include <stdio.h>
#include <errno.h>
#include "myAssert.h"

/**
 * \brief A function that prints a char massive to sdout
 * 
 * \param[in] char* str - array to be printed 
 * 
 * \return -1 of an error occured, 0 if no error
 **/
int putsMy (char* str);

/**
 * \brief A function that compares two strings
 * 
 * \param[in] const char* str1 - pointer to the start of the first char array
 * \param[in] const char* str2 - pointer to the start of the second char array
 * 
 * \return Returns the difference of the strings
 **/
int strcmpMy (const char* str1, const char* str2);

/**
 * \brief A function that calculates the length of given string
 * 
 * \param[in] const char *str - pointer to the start of the char array
 * 
 * \return Returns the length of the string
 **/
size_t strlenMy (const char *str);

/**
 * \brief A function that copies the char array to a buffer
 * 
 * \param[in] char* destStr - pointer to the start of the buffer
 * \param[in] char* srcStr  - pointer to the start of the source char
 * 
 * \returns The pointer to the buffer
 **/
char* strcpyMy (char* destStr, const char* srcStr);

/**
 * \brief A function that copies the char array to a buffer
 * 
 * \param[in] char* destStr - pointer to the start of the buffer
 * \param[in] char* srcStr  - pointer to the start of the source char
 * \param[in] size_t amount - the maximum amount of elements to be copied
 * 
 * \returns The pointer to the buffer
 **/
char* strncpyMy (char* destStr, const char* srcStr, size_t amount);

/**
 * \brief A function returns a pointer to the first occurrence 
 * of the character symbol in the string str. Works for constant values!!!
 * 
 * \param[in] const char *str - pointer to the start of the char array
 * \param[in] int symbol - The ASCII code for the symbol
 * 
 * \return Returns the place of the symbol in str
 **/
const char* strchrMy_c (const char *str, int symbol);

/**
 * \brief A function returns a pointer to the first occurrence 
 * of the character symbol in the string str. Works for non - constant values!!!
 * 
 * \param[in] const char *str - pointer to the start of the char array
 * \param[in] int symbol - The ASCII code for the symbol
 * 
 * \return Returns the place of the symbol in str
 **/
      char* strchrMy   (      char *str, int symbol);

/**
 * \brief A function that reads  in  at  most one less than size characters from stream and stores them into the buffer pointed to by s.  
 * Reading stops after an EOF or a newline.  If a newline is
 * read, it is stored into the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
 *
 * \param[in] char *str    - pointer to the char array where we put the read strings
 * \param[in] int maxSize  - maximum elements to be read
 * \param[in] FILE* stream - a pointer to the FILE struct which helps us to read from the file  
 **/
char *fgetsMy (char *str, int maxSize, FILE* stream);

/**
 * \brief A function that prints an array of pointers to char into stdout
 * 
 * \param[in] char* text[] - pointer to array of char pointers
 * \param[in] size_t rows  - amount of rows in the file
 * \param[in] FILE* outputFile - a pointer to the FILE struct from which we read 
 **/
void printText (char* text[], size_t rows, FILE* outputFile);

/**
 * \brief function  returns  a  pointer  to  a  new string which is a duplicate of the string s.  Memory for the new string is obtained with malloc(3), and can be freed with
 *      free(3).
 *
 * \param[in] const char* srcStr - pointer to the source string
 *
 * \return Returns the pointer to the created buffer
 **/
char* strdupMy (const char* srcStr);

/**
 * \brief A function that concatenates two strings
 *
 * \param[in] char *destStr - string to which we concatenate
 * \param[in] char *srcStr  - string from which we concatenate
 **/
char *strcatMy (char *destStr, const char *srcStr);

/**
 * \brief A function that concatenates two strings, at max amount size of elements
 *
 * \param[in] char *destStr - string to which we concatenate
 * \param[in] char *srcStr  - string from which we concatenate
 * \param[in] size_t amount - number of elements to be concatenated 
 **/
char *strncatMy (char *destStr, const char *srcStr, size_t amount);




