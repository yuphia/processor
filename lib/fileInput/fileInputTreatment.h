/**
 * \file fileInputTreatment.h
 *
 * \brief A file that contains functions to work with files
 **/

#ifndef FILEINPUTTREATMENT_H

#define FILEINPUTTREATMENT_H    

#include "myAssert.h"
#include <stdio.h>
#include <cstring>
#include <iostream>

/**
 * \brief A structure that is used to contain text inputted from file 
 *
 * \param struct Line* lines - an array of lines
 * \param char* textArray    - buffer that holds the text
 * \param size_t textSize    - size of the text
 * \param size_t nLines      - number of lines that text consists of
 **/
struct Text
    {
        struct Line* lines;
        char* textArray;
        size_t textSize;
        size_t nLines;
    };

/**
 * \brief A structure that is used to contain a line and its size
 *
 * \param char* line - a buffer that holds the line
 * \param size_t lineSize - the number of elements in the line
 **/
struct Line
    {
        char* line;
        size_t lineSize;
    };

/**
 * \brief A function that checks if the line is empty or not
 *
 * \param[in] char* line - the line to be checked
 *
 * \return Returns 1 if is empty, 0 if is not
 **/
bool isLineEmpty (char* line);

/**
 * \brief A function that counts an amount of char elements in the file
 *
 * \param[in] FILE* inputFile - the file to be read from
 **/
size_t getFileSize (FILE* inputFile);

/**
 * \brief A function that checks if the pointer to the FILE struct is non-zero
 *
 * \param[in] FILE* file - pointer to the file struct which we check
 *
 * \return Returns 1 if the pointer is valid, 0 if is not
 **/
bool isFile (FILE* file);

/**
 * \brief A wrap for bufferization, the wrapped function transits the text from the file to the Text struct
 *
 * \param[in] FILE* inputFile   - pointer to the file struct from whick we take the input
 * \param[in] struct Text* text - pointer to the text struct were we put the text
 **/
void transitFileToText (FILE* inputFile, struct Text* text);

/**
 * \brief A function that is wrapped be transitFileToText
 *
 * \param[in] FILE* inputFile   - file from which we input the text
 * \param[in] struct Text* text - struct to which we put the text
 **/
void fillText (FILE* inputFile, struct Text* text);

/**
 * \brief A function that counts the amount of lines in an array of chars
 *
 * \param[in] char* text      - pointer to the text
 * \param[in] size_t textSize - size of the buffer
 *
 * \return Returns the number of lines  
 **/
size_t countLines (char* text, size_t textSize);

/**
 * \brief A function that converts a text struct into an array of line structs
 *
 * \param[in] size_t* lineAmount - pointer to the amount of lines
 * \param[in] char* text         - pointer to the buffer of text
 *
 * \return Returns a pointer to the buffer of line structs filled with the text
 **/
struct Line* transitTextToLineArray (size_t* lineAmount, char* text);

/**
 * \brief A function that prints a textStruct into a file
 *
 * \param[in] struct Text* text - pointer to the text struct
 * \param[in] FILE* fileOut     - pointer to the FILE struct where we print the text
 **/
void printTextStruct (struct Text* text, FILE* fileOut);

/**
 * \brief A function frees the bufferized array of struct lines
 *
 * \param[in] struct Line* lines - pointer to the struct line array
 **/
void freeArrayLines (struct Line* lines);

/**
 * \brief A function that combines the usage of two functions transitTextToLineArray 
 * and transitFileToTextArray
 *
 * \param[in] FILE* inputFile - pointer to the FILE struct form which we input
 * \param[in] struct Text* text - pointer to the text struct which will hold the text and line array
 **/
void transitFileToLineArray (FILE* inputFile, struct Text* text);

/**
 * \brief A function that prints and line array
 *
 * \param[in] FILE* file        - pointer to the FILE struct from which we input
 * \param[in] struct Text* text - pointer to the text struct into which we input
 **/
void printLinesArray (FILE* file, struct Text* text);

/**
 * \brief A function that checks all '\0' symbols to '\n' in the char array
 *
 * \param[in] char* text - pointer to the char array
 * \param[in] size_t
 **/
void runThroughText (char* text, size_t textSize);

void markerNormalSortStart (FILE* file);
void markerNormalSortEnd (FILE* file);
void markerReverseSortStart (FILE* file);
void markerReverseSortEnd (FILE* file);
void markerNoSortStart (FILE* file);
void markerNoSortEnd (FILE* file);

#endif
