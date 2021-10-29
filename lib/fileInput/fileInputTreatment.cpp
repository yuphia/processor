#include "fileInputTreatment.h"

size_t getFileSize (FILE* inputFile)
{
    MY_ASSERT (inputFile != 0, "Trying to reach for address nullptr")

    fseek (inputFile, 0, SEEK_END);
    long int fileSize = ftell (inputFile);
    if (fileSize < 0)
        return 0;

    fseek (inputFile, 0, SEEK_SET);

    return (size_t)fileSize;
}

bool isFile (FILE* file)
{
    return (file != nullptr) ? true : false;
}

void transitFileToText (FILE* inputFile, struct Text* text)
{
    MY_ASSERT (isFile (inputFile), "Pointer to inputFile struct is nullptr");
    MY_ASSERT (text != nullptr, "Pointer to textArray is nullptr");

    text ->  textSize = getFileSize (inputFile);
    text -> textArray = (char*)calloc (text -> textSize + 1, sizeof(char));

    if ((text -> textArray) == nullptr)
        return;

    fillText (inputFile, text);
}

void fillText (FILE* inputFile, struct Text* text)
{
    MY_ASSERT (isFile (inputFile), "Pointer to inputFile struct is nullptr");
    MY_ASSERT (text != nullptr, "Pointer to textArray is nullptr");

    fread (text -> textArray, sizeof(char), text -> textSize, inputFile);
    *(text -> textArray + text -> textSize) = '\n';
    fseek (inputFile, 0, SEEK_SET);
}

size_t countLines (char* text, size_t textSize)
{
    MY_ASSERT (text != nullptr, "Pointer to text = nullptr");

    char* lineStartTrue = text;
    char* lineStartCheck = text;
    size_t lineCount = 0;

    while ( ( lineStartCheck = strchr (lineStartTrue, '\n')) != NULL && 
     (size_t)(lineStartCheck - text) < textSize)
    {
        lineStartTrue = lineStartCheck + 1;
        lineCount++;
    }

    return lineCount;
}

void transitFileToLineArray (FILE* inputFile, struct Text* text)
{
    transitFileToText (inputFile, text);

    text -> nLines = countLines (text -> textArray, text -> textSize);

    text -> lines = transitTextToLineArray (&text -> nLines, text -> textArray);
}

struct Line* transitTextToLineArray (size_t* lineAmount, char* text)
{
    MY_ASSERT (text != nullptr, "Pointer to text = nullptr");
    MY_ASSERT (text != nullptr, "Pointer to an array of structs Line = nullptr");

    struct Line* arrayOfStrings = (struct Line*) calloc (*lineAmount, sizeof(struct Line)); //free

    char* endOfLine = text;
    char* startOfLine = text;
    size_t termChars = 0;

    for (size_t i = 0; i < *lineAmount; i++)
    {
        endOfLine = strchr (startOfLine, '\n');

        if (endOfLine - startOfLine > 2 && *(endOfLine - 1) == '\r')
        {
            *(endOfLine - 1) = '\0';
            endOfLine--;
            termChars = 2;
        }
        else
        {
            *endOfLine = '\0';
            termChars = 1;
        }

        if (!isLineEmpty (startOfLine))
        {
            arrayOfStrings[i].line = startOfLine;
            arrayOfStrings[i].lineSize = (size_t)(endOfLine - startOfLine);

            startOfLine = endOfLine + termChars;
        }
        else
        {
            i--;
            (*lineAmount)--;
            startOfLine = endOfLine + termChars;
        }
    }

    arrayOfStrings = (struct Line*)realloc (arrayOfStrings, 
                                   (size_t)(endOfLine - text) * sizeof(struct Line*));

    return arrayOfStrings;
}

void printTextStruct (struct Text* text, FILE* fileOut)
{
    MY_ASSERT (text != nullptr, "Pointer to text = nullptr");
    MY_ASSERT (fileOut != nullptr, "Pointer to output file = nullpt");

    fwrite (text -> textArray, text -> textSize, sizeof(char), fileOut);
}

void freeArrayLines (struct Line* lines)
{
    free (lines);
}

void printLinesArray (FILE* file, struct Text* text)
{
    MY_ASSERT (text != nullptr, "Pointer to text = nullptr");    
    for (size_t i = 0; i < text -> nLines; i++)
    {
        //fprintf (stdout, "%s\n", text -> lines[i].line);
        fwrite (text -> lines[i].line, text -> lines[i].lineSize, sizeof(char), file);
        fprintf (file, "\n");
    }
}

void runThroughText (char* text, size_t textSize)
{
    MY_ASSERT (text != nullptr, "Pointer to text = nullptr");

    char* lineStartTrue = text;
    char* lineStartCheck = text;

    while ( ( lineStartCheck = strchr (lineStartTrue, '\0')) != NULL && 
     (size_t)(lineStartCheck - text) < textSize - 1)
    {
        lineStartTrue = lineStartCheck + 1;
        *lineStartCheck = '\n';
    }
} 

bool isLineEmpty (char* line)
{
    for (; *line != '\0'; line++)
    {
        if (isalpha(*line))
            return 0;
    }

    return 1;
}

void markerNormalSortStart (FILE* file)
{
    fprintf(
           file,
           "\n"
           "\n"
           "\n"
           "############################################"
           "    SORTING TEXT FROM THE BEGINNING    "
           "############################################"
           "\n"
           "\n"
           "\n");
}

void markerNormalSortEnd (FILE* file)
{ 
    fprintf(
           file,
           "\n"
           "\n"
           "\n"
           "############################################"
           "    FINISHED SORTING TEXT FROM THE BEGINNING    "
           "############################################"
           "\n"
           "\n"
           "\n");
}

void markerReverseSortStart (FILE* file)
{
    fprintf(
           file,
           "\n"
           "\n"
           "\n"
           "############################################"
           "    SORTING TEXT FROM THE END   "
           "############################################"
           "\n"
           "\n"
           "\n");
}

void markerReverseSortEnd (FILE* file)
{ 
    fprintf(
           file,
           "\n"
           "\n"
           "\n"
           "############################################"
           "    FINISHED SORTING TEXT FROM THE END  "
           "############################################"
           "\n"
           "\n"
           "\n");
}

void markerNoSortStart (FILE* file)
{ 
    fprintf(
           file,  
           "\n"
           "\n"
           "\n"
           "############################################"
           "    DUMPING THE ORIGINAL TEXT   "
           "############################################"
           "\n"
           "\n"
           "\n");
}

void markerNoSortEnd (FILE* file)
{ 
    fprintf
          (
           file,
           "\n"
           "\n"
           "\n"
           "############################################"
           "    FINISHED DUMPING THE ORIGINAL TEXT  "
           "############################################"
           "\n"
           "\n"
           "\n");
}
