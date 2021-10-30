#ifndef ASS_FUNCTIONS_H

#define ASS_FUNCTIONS_H 1

#include "../lib/SortingAlg/sort.h"
#include "../lib/StrFuncs/strlibMy.h"
#include "../lib/fileInput/fileInputTreatment.h"
#include "../lib/commands/commands.h"
#include "../lib/MistakeHandling/myAssert.h"

#define write(cmd)\
        char thisCmdN = cmd;\
        fwrite (&thisCmdN, sizeof(char), 1, asmHere);

enum compilationErrs 
        {
        NO_ERROR = 0,
        UNRECOGNISED_COMMAND = 1,
        MISSED_ARGUMENT = 2,
        TOO_MANY_ARGUMENTS = 3,
        WRITING_ERROR = 4        
        };

struct errorInfo
        {
        enum compilationErrs compilationStatus;
        size_t nLine;
        char* line;
        };

struct cmdField
        {
        unsigned char reg : 1;
        unsigned char mem : 1;
        unsigned char imm : 1;
        unsigned char cmd : 5;
        };

void getCode (FILE* const code, struct Text *codeText);

enum compilationErrs parseLine (struct Line* line, FILE* const asmHere);

struct errorInfo *compileCodeMain (struct errorInfo*, struct Text *codeText, 
                                   FILE* const asmHere);

enum compilationErrs compileCode     (struct Text *codeText, FILE* const asmHere);

enum compilationErrs putToCode (FILE* const asmHere, char* cmd, 
                                char* line, double* arg);

enum compilationErrs getArgument (char* line, double* argument);

char* skipCmd (char* str);

void printErrorInfo (struct errorInfo* pInfo);
void printSplitter ();

const double poisonProc = 0xFFFFFF;
static const char splitter[] = 
            "============================================================";

#endif
