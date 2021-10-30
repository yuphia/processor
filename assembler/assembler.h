#include "../lib/SortingAlg/sort.h"
#include "../lib/StrFuncs/strlibMy.h"
#include "../lib/fileInput/fileInputTreatment.h"
#include "../lib/commands/commands.h"

enum compilationErrs 
        {
        NO_ERROR = 0,
        UNRECOGNISED_COMMAND = 1,
        MISSED_ARGUMENT = 2,
        TOO_MANY_ARGUMENTS = 3        
        };

struct errorInfo
        {
        enum compilationErrs compilationStatus;
        size_t nLine;
        char* line;
        };

void getCode (FILE* const code, struct Text *codeText);

enum compilationErrs parseLine (struct Line* line, FILE* const asmHere);

struct errorInfo *compileCodeMain (struct errorInfo*, struct Text *codeText, 
                                   FILE* const asmHere);

enum compilationErrs compileCode     (struct Text *codeText, FILE* const asmHere);

enum compilationErrs putToCode (FILE* const asmHere, char* cmd, double arg, char* line);

void printErrorInfo (struct errorInfo* pInfo);
void printSplitter ();

const double poisonProc = 0xFFFFFF;
static const char splitter[] = 
            "============================================================";

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
    double arg = 0xFFFFFF;

    sscanf (line->line, "%s", cmd);/*%lg*/
    sscanf (line->line, "%lg", &arg);
    printf ("arg = %lg", arg);

    enum compilationErrs compilationStatus = putToCode (asmHere, cmd, arg, line->line);
           
    return compilationStatus;
}

enum compilationErrs putToCode (FILE* const asmHere, char* cmd, double arg, char* line)
{
    if (strcmp (cmd, "push") == 0)
    {
        fprintf (asmHere, "%lg%lg", (double)PUSH, arg);
        if (arg == poisonProc)
            return MISSED_ARGUMENT;
    }

    else if (strcmp (cmd, "pop") == 0)
    {
        fprintf (asmHere, "%lg", (double)POP);         
        if (arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }
    
    else if (strcmp (cmd, "hlt") == 0)
    { 
        fprintf (asmHere, "%lg", (double)HALT);
        if (arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }

    else if (strcmp (cmd, "add") == 0)
    {
        fprintf (asmHere, "%lg", (double)ADD);
        if (arg != poisonProc)
            return TOO_MANY_ARGUMENTS;
    }

    else if (strcmp (cmd, "mul") == 0)
    {
        fprintf (asmHere, "%lg", (double)MUL);
        if (arg != poisonProc)
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
        case UNRECOGNISED_COMMAND: 
            printf ("Compilation error occured, unrecognised command in text\n");
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
    fflush (stdin);
}

char* skipCmd (char* str)
{
    for (size_t currentSymbol = 0; currentSymbol < strlen (str); currentSymbol++);
    
    if (currentSymbol == strlen (str) - 1)
        return 0;

    return str + currentSymbol;
}
