/** \file main.cpp
 * \brief All main calls are located in this file 
 **/

/** \mainpage Onegin. A program used to sort your input text in alphabetical and reverse (from the end) order.*/

#include <stdio.h>
#include <iostream>
#include "strlibMy.h"
#include "sort.h"
#include "fileInputTreatment.h" 
#include <cstring>

const int MAXROWLENGTH = 100;
const int MAXROW = 27000;//27000;

void arrayFree (char *arrayText[], size_t arraySize);

bool checkSortStr (void **array, int size);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf ("FORMAT FOR RUNNING: %s INPUTFILENAME OUTPUTFILENAME\n", argv[0]);
        return 0;
    }

    struct Text text = {};
    
    FILE* inputFile = fopen (argv[1], "rb");

    if (inputFile == nullptr)
    {
        printf ("Pointer to inputFile equals to nullptr");
        return 1;
    }

    transitFileToLineArray (inputFile, &text);

    fclose (inputFile);

    FILE* outputFile = fopen (argv[2], "wb");

    if (outputFile == nullptr)
    {
        printf ("Pointer to outputFile is equal to nullptr");
        return 1;
    }

    qsort (text.lines, text.nLines, sizeof (struct Line), compareLineStruct);
    
    markerNormalSortStart (outputFile);
    printLinesArray (outputFile, &text);
    markerNormalSortEnd (outputFile);

    qsort (text.lines, text.nLines, sizeof (struct Line), compareLineStructEnd);

    markerReverseSortStart (outputFile);
    printLinesArray (outputFile, &text);
    markerReverseSortEnd (outputFile);
    
    runThroughText (text.textArray, text.textSize);

    markerNoSortStart (outputFile);
    printTextStruct (&text, outputFile);
    markerNoSortEnd (outputFile);

    fclose (outputFile);  

    free (text.textArray);

    freeArrayLines (text.lines);

    return 0;
}


void arrayFree (char *arrayText[], size_t arraySize)
{
    MY_ASSERT (arrayText != nullptr, "pointer to arrayText is equal to nullptr");
    printf ("rows = %zu\n", arraySize);

    for (size_t i = 0; i < arraySize; i++)
    {
        if (arrayText[i])
            free (arrayText [i]);
    }
}


bool checkSortStr (void **array, int size)
{
    MY_ASSERT (array != nullptr, "pointer to array is equal to nullptr");

    for (int i = 0; i < size - 1; i++)
    {
        MY_ASSERT ((char**)array[i] != nullptr, "pointer to array[i] is equal to nullptr");

        if (strcmp ((char*)array[i], (char*)array[i + 1]) > 0)
            return false;
    }

    return true;
}







