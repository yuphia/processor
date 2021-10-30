#include "assFunctions.h"

void getCode (FILE* const code, struct Text *codeText)
{
    transitFileToLineArray (code, codeText);
}

struct errorInfo *compileCodeMain (struct errorInfo* info, struct Text *codeText,
                                   FILE* const asmHere)
{
    size_t codeSize = codeText->nLines;

    for (size_t currLine = 0; currLine < codeSize; currLine++)
    {
        enum compilationErrs compilationStatusIn = 
            parseLine ((codeText->lines) + currLine, asmHere);

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

enum compilationErrs parseLine (struct Line* line, FILE* const asmHere)
{
    char cmd[5] = "";
    double arg = poisonProc;

    sscanf (line->line, "%s", cmd);/*%lg*/
    
    enum compilationErrs compilationStatus = putToCode (asmHere, cmd, line->line, &arg);
           
    return compilationStatus;
}

enum compilationErrs putToCode (FILE* const asmHere, char* cmd,
                                char* line, double* arg)
{
    if (strcmp (cmd, "push") == 0)
    {
        write (PUSH);

        if (getArgument (line, arg) != NO_ERROR)
            return MISSED_ARGUMENT;

        if (fwrite (arg, sizeof(double), 1, asmHere) != 1)
            return WRITING_ERROR;

        return NO_ERROR; 
    }

    else if (strcmp (cmd, "pop") == 0)
    {                 
        write (POP);          

        if (*arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }
    
    else if (strcmp (cmd, "hlt") == 0)
    {
        write (HALT); 
        
        if (*arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }

    else if (strcmp (cmd, "add") == 0)
    {
        write (ADD);
        if (*arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }

    else if (strcmp (cmd, "mul") == 0)
    {
        write (MUL);
                
        if (*arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }

    else
    {
        fprintf (asmHere, "Error compiling, unrecognised command\n");

        return UNRECOGNISED_COMMAND;
    }

    return NO_ERROR;
}

enum compilationErrs compileCode (struct Text *codeText, FILE* const asmHere)
{
    struct errorInfo info = {NO_ERROR, 0, nullptr};
    struct errorInfo* pInfo = nullptr;
    pInfo = compileCodeMain (&info, codeText, asmHere);

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

enum compilationErrs getArgument (char* line, double* argument)
{
    char* pointerToArg = skipCmd (line);
    //printf ("pointer to argument = %p", (void*) pointerToArg);

    if (pointerToArg == nullptr)
    {
        return MISSED_ARGUMENT;    
    }

    int scanfReturn = sscanf (pointerToArg, "%lg", argument);

    if (*argument == poisonProc  && scanfReturn == 1)
        return MISSED_ARGUMENT;

    return NO_ERROR;
} 

