#include "assFunctions.h"

void getCode (FILE* const code, struct Text *codeText)
{
    MY_ASSERT (code != nullptr, "A mistake happened while opening code file\n");
    MY_ASSERT (codeText != nullptr, "Pointer to codeText is equal to nullptr\n");
    
    transitFileToLineArray (code, codeText);
}

struct errorInfo *compileCodeMain (struct errorInfo* info, struct Text *codeText)
{
    MY_ASSERT (info != nullptr, "pointer to info struct is equal to nullptr\n");
    MY_ASSERT (codeText != nullptr, "pointer to codeText equals nullptr\n");
    
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
    MY_ASSERT (line != nullptr, "pointer to line equals nullptr\n");

    char cmd[5] = "";
    double arg = poisonProc;

    sscanf (line->line, "%s", cmd);/*%lg*/
    
    enum compilationErrs compilationStatus = putToCode (cmd, line->line, &arg);
           
    return compilationStatus;
}

enum compilationErrs putToCode (char* cmd, char* line, double* arg)
{
    FILE* const asmHere = fopen ("code+asm/asm.txt", "ab");
    MY_ASSERT (asmHere != nullptr, "An error occurred while opening assembler file\n");
    MY_ASSERT (line != nullptr, "Pointer to line array is nullptr\n");
    MY_ASSERT (line != nullptr, "Pointer to arg is equal to nullptr\n");

    if (strcmp (cmd, "push") == 0)
    {
        enum compilationErrs argErr = getArgument (line, arg, PUSH, asmHere);
        if (argErr != NO_ERROR)
        {
            printf ("argErr = %d", argErr);
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
        WRITE (POP);          

        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }
    
    else if (strcmp (cmd, "hlt") == 0)
    {
        WRITE (HALT); 
        
        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }

    else if (strcmp (cmd, "add") == 0)
    {
        WRITE (ADD);
        if (*arg != poisonProc)
        {
            fclose (asmHere);
            return TOO_MANY_ARGUMENTS;
        }
    }

    else if (strcmp (cmd, "mul") == 0)
    {
        WRITE (MUL);
                
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
    MY_ASSERT (codeText != nullptr, "Pointer to codeText is equal to nullptr\n");

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

        case FORBIDDEN_ARGUMENT:
            printf ("You are using an argument that can't be used as an input"                    
                    " (check poisonProc constant)\n");
            printSplitter();
            break;

        case TOO_MANY_ARGUMENTS:
            printf ("Too many arguments for a function\n");
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

        case WRONG_REG_ERROR:
            printf ("Check your register name in this line (accepted register names:"
                    "ax, bx, cx, dx)\n");
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
    MY_ASSERT (pInfo != nullptr, "Pointer to pInfo struct is equal to nullptr\n");

    printf ("\n\n%s\n", splitter);
    printf ("An error has occured while compiling\n");
    printf ("While compiling this command: %s\n", pInfo->line);
    printf ("In line: %zu\n", pInfo->nLine + 1); 

    fflush (stdin);
}

void printSplitter ()
{
    printf ("%s\n\n", splitter);
    fflush (stdout);
}

char* skipCmd (char* str)
{
    MY_ASSERT (str != nullptr, "Pointer to str is equal to nullptr\n");
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
    MY_ASSERT (line != nullptr, "Pointer to line is equal to nullptr\n");
    MY_ASSERT (argument != nullptr, "Pointer to argument is equal to nullptr\n");
    MY_ASSERT (asmHere != nullptr, "An error occurred while opening asmHere file\n");

    char* pointerToArg = skipCmd (line);
    //printf ("pointer to argument = %p", (void*) pointerToArg);
    bool isMemory    = false;
    bool isRegister  = false;
    bool isImmidiate = false;

    enum Reg reg = WRONG_REG;

    if (pointerToArg == nullptr)
    {   
        return MISSED_ARGUMENT;    
    }  
    enum compilationErrs checkMem = isMemoryCommand (&pointerToArg, &isMemory);
    
    if (checkMem != NO_ERROR)
        return checkMem; 
    
    enum compilationErrs checkImmAndReg = isImmRegDetection (pointerToArg, &isRegister,
                                                             &isImmidiate, argument, &reg);

    if (checkImmAndReg != NO_ERROR)
        return checkImmAndReg;
    
    if (isRegister == 1 && reg == WRONG_REG)
        return WRONG_REG_ERROR;

    FILL_FIELD_AND_WRITE();

    return NO_ERROR;
} 

enum compilationErrs isMemoryCommand (char** line, bool* isMemory)
{
    MY_ASSERT (line != nullptr, "pointer to pointer to line is equal to nullptr\n");
    MY_ASSERT (*line != nullptr, "pointer to line is equal to nullptr\n");
    MY_ASSERT (isMemory != nullptr, "pointer to isMemory is equal to nullptr\n");
    
    size_t placeOfCurrEl = 0;

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
            if (*line + placeOfCurrEl == openingBracket || 
                *line + placeOfCurrEl == closingBracket)
            {             
            *(*line + placeOfCurrEl) = ' ';       
            }        
        }

        *line = jumpToLastSpace (*line);
    
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

enum compilationErrs isImmRegDetection (char* line, bool* isRegister,
                                        bool* isImmidiate,
                                        double* arg, enum Reg* reg)
{
    MY_ASSERT (line != nullptr, "Pointer to line is equal to nullptr\n");
    MY_ASSERT (isRegister != nullptr, "Pointer to isRegister is equal to nullptr\n");
    MY_ASSERT (isImmidiate != nullptr, "Pointer to isImmidiate is equal to nullptr\n");
    MY_ASSERT (arg != nullptr, "Pointer to arg is equal to nullptr\n");
    MY_ASSERT (reg != nullptr, "Pointer to reg is equal to nullptr\n");
    
    static size_t runThrough = 0;

    runThrough++;

    line = jumpToLastSpace (line);

    int checkPointer = 0;

    char* regName = (char*)calloc (sizeof(line), sizeof (char));
    MY_ASSERT (regName != nullptr, "Pointer to regName equals nullptr\n");      

    sscanf (line, "%1sx+%n%lg", regName, &checkPointer, arg);         
    if (checkPointer == 3 && *arg != poisonProc)
    {
        *reg = detectRegister (regName);
        if (*reg == WRONG_REG)
            return WRONG_REG_ERROR;

        if (*arg == poisonProc)
            return FORBIDDEN_ARGUMENT;

        *isRegister  = 1;
        *isImmidiate = 1;
        
        free (regName);
        return NO_ERROR;
    }
    
    sscanf (line, "%1sx%n", regName, &checkPointer);
    if (checkPointer == 2)
    {
        *reg = detectRegister (regName);
        if (*reg == WRONG_REG)
            return WRONG_REG_ERROR;

        *isRegister = 1;
        
        free (regName);
        return NO_ERROR;
    }

    sscanf (line, "%lg", arg);    
    if (*arg != poisonProc)
    {
        if (*arg == poisonProc)
            return FORBIDDEN_ARGUMENT;

        *isImmidiate = 1;        
        free (regName);
        return NO_ERROR;
    }

    free(regName);
    return MISSED_ARGUMENT;
}

enum Reg detectRegister (char* regName)
{
    MY_ASSERT (regName != nullptr, "pointer to regName is equal to nullptr\n");

    if (isRegOk (regName))
        return WRONG_REG;

    if (*regName == 'a')
        return AX;
    else if (*regName == 'b')
        return BX;
    else if (*regName == 'c')
        return CX;
    else if (*regName == 'd')
        return DX;

    return WRONG_REG;
}

bool isRegOk (char* regName)
{
    MY_ASSERT (regName != nullptr, "pointer to regName is equal to nullptr\n");
 
    size_t i = 1;
    for (; i < sizeof(regName) && *regName != 0; i++);

    return (i == sizeof (regName) - 1) ? 1 : 0;
}

char* jumpToLastSpace (char* line)
{
    MY_ASSERT (line != nullptr, "pointer to line is equal to nullptr\n");

    size_t thisSymbolPlace = 0;
    for (; thisSymbolPlace < sizeof(line); thisSymbolPlace++)
        if (*(line + thisSymbolPlace) != ' ')
            return line + thisSymbolPlace;

   return line + thisSymbolPlace; 
}
