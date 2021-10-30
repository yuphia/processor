#include "assFunctions.h"

void getCode (FILE* const code, struct Text *codeText)
{
    transitFileToLineArray (code, codeText);
}

struct errorInfo *compileCodeMain (struct errorInfo* info, struct Text *codeText)
{
    size_t codeSize = codeText->nLines;

    for (size_t currLine = 0; currLine < codeSize; currLine++)
    {
        enum compilationErrs compilationStatusIn = 
            parseLine ((codeText->lines) + currLine);

        if (compilationStatusIn != NO_ERROR)
        {
            info->compilationStatus = compilationStatusIn;
            info->nLine = currLine;
            info->line  = ((codeText->lines) + currLine)->line;
            return info;    
        }
    }

    return info;
}

enum compilationErrs parseLine (struct Line* line)
{
    char cmd[5] = "";
    double arg = poisonProc;

    sscanf (line->line, "%s", cmd);/*%lg*/
    
    enum compilationErrs compilationStatus = putToCode (cmd, line->line, &arg);
           
    return compilationStatus;
}

enum compilationErrs putToCode (char* cmd, char* line, double* arg)
{
    FILE* const asmHere = fopen ("code+asm/asm.txt", "ab");
    MY_ASSERT (asmHere != nullptr, "An error occurred while opening assembler file");

    if (strcmp (cmd, "push") == 0)
    {
        enum compilationErrs argErr = getArgument (line, arg, PUSH, asmHere);
        if (argErr != NO_ERROR)
        {
            fclose (asmHere);
            return argErr;
        }

        if (fwrite (arg, sizeof(double), 1, asmHere) != 1)
        {
            fclose (asmHere);
            return WRITING_ERROR;
        }
    }

    else if (strcmp (cmd, "pop") == 0)
    {                 
        write (POP);          

        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }
    
    else if (strcmp (cmd, "hlt") == 0)
    {
        write (HALT); 
        
        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }

    else if (strcmp (cmd, "add") == 0)
    {
        write (ADD);
        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }

    else if (strcmp (cmd, "mul") == 0)
    {
        write (MUL);
                
        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }

    else
    {
        fprintf (asmHere, "Error compiling, unrecognised command\n");

        fclose (asmHere);
        return UNRECOGNISED_COMMAND;
    }

    fclose (asmHere);
    return NO_ERROR;
}

enum compilationErrs compileCode (struct Text *codeText)
{
    struct errorInfo info = {NO_ERROR, 0, nullptr};
    struct errorInfo* pInfo = nullptr;
    pInfo = compileCodeMain (&info, codeText);

    if (pInfo->compilationStatus != NO_ERROR)
        printErrorInfo (pInfo);

    switch (pInfo->compilationStatus)
    {   
        case WRITING_ERROR:
            printf ("Couldn't write to the code file\n");
            printSplitter();
            break;

        case UNRECOGNISED_COMMAND: 
            printf ("Compilation error occurred, unrecognised command in text\n");
            printSplitter();
            break;

        case MISSED_ARGUMENT:
            printf ("You forgot to put an argument (or your argument is equal to %lg)\n",
                         poisonProc);
            printSplitter();
            break;

        case TOO_MANY_ARGUMENTS:
            printf ("\nToo many arguments for a function\n");
            printSplitter();
            break;

        case NO_ERROR:
            printf ("Compilation was successful\n"); 
            break;

        case STRAY_OPEN_BRACKET:
            printf ("[ is missing a closing bracket\n");
            printSplitter();
            break;

        case STRAY_CLOSE_BRACKET:
            printf ("] is missing an opening bracket\n");
            printSplitter();
            break;

        case EXTRA_BRACKETS:
            printf ("Too many [ or ] expressions like this don't work [[]]\n");
            printSplitter();
            break;

        default:
            printf ("Unknown error\n");
            break;
    }

    return pInfo->compilationStatus;
}

void printErrorInfo (struct errorInfo* pInfo)
{
    printf ("\n\n%s\n", splitter);
    printf ("An error has occured while compiling\n");
    printf ("While compiling this command: %s\n", pInfo->line);
    printf ("In line: %zu\n", pInfo->nLine); 

    fflush (stdin);
}

void printSplitter ()
{
    printf ("%s\n\n", splitter);
    fflush (stdout);
}

char* skipCmd (char* str)
{
    size_t currentSymbol = 0;
    for (; currentSymbol < strlen (str) && *(str + currentSymbol) != ' ';
                                                             currentSymbol++);     

    if (currentSymbol >= strlen (str) - 1)
        return nullptr;

    return str + currentSymbol;
}

enum compilationErrs getArgument (char* line, double* argument, 
                                  enum commands cmd, FILE* const asmHere)
{
    char* pointerToArg = skipCmd (line);
    //printf ("pointer to argument = %p", (void*) pointerToArg);
    bool isMemory    = false;
    bool isRegister  = false;
    bool isImmidiate = false;

    enum compilationErrs checkMem = isMemoryCommand (&pointerToArg, &isMemory);

    if (checkMem != NO_ERROR)
        return checkMem;
    
    if (pointerToArg == nullptr)
    {
        return MISSED_ARGUMENT;    
    }

    int scanfReturn = sscanf (pointerToArg, "%lg", argument);

    if (*argument == poisonProc  && scanfReturn == 1)
        return MISSED_ARGUMENT;

    fillFieldAndWrite();

    //printf ("isMemory = %d\n", thisCmd.mem);   
    //printf ("cmd = %d\n", thisCmd.cmd);
    //write (thisCmd.cmd);

    return NO_ERROR;
} 

enum compilationErrs isMemoryCommand (char** line, bool* isMemory)
{
    char newLine[100] = "";

    size_t placeOfCurrEl = 0;
    size_t realPlace = 0;

    char* openingBracket  = strchr (*line, '[');
    char* closingBracket  = strchr (*line, ']');

    enum compilationErrs bracketStatus = 
        isBracketStructureOk (openingBracket, closingBracket);

    if (bracketStatus != NO_ERROR)
        return bracketStatus;

    if (openingBracket != nullptr)
    {
        *isMemory = true;
        for (; placeOfCurrEl < strlen (*line); placeOfCurrEl++)
        {
            if (*line + placeOfCurrEl != openingBracket && 
                *line + placeOfCurrEl != closingBracket)
            {             
            newLine [realPlace] = *(*line + placeOfCurrEl);
            realPlace++;            
            }
        }

        *line = newLine;

        if (strchr (*line, '[') != nullptr || strchr (*line, ']') != nullptr)
            return EXTRA_BRACKETS;
    }

    return NO_ERROR;
}

enum compilationErrs isBracketStructureOk (char* oBracket, char* cBracket)
{
    if (oBracket != nullptr && cBracket == nullptr)
        return STRAY_OPEN_BRACKET;

    if (oBracket == nullptr && cBracket != nullptr)
        return STRAY_CLOSE_BRACKET;

    return NO_ERROR;
}
