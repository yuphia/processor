#ifndef ASS_FUNCTIONS_H

#define ASS_FUNCTIONS_H 1

#include "sort.h"
#include "strlibMy.h"
#include "fileInputTreatment.h"
#include "commands.h"
#include "myAssert.h"

#define write(cmd)\
        char thisCmdN = cmd;\
        fwrite (&thisCmdN, sizeof(char), 1, asmHere);

#define fillFieldAndWrite()\
            struct cmdField thisCmd = {isRegister, isMemory, isImmidiate, cmd};\
            write (thisCmd.cmd + thisCmd.mem*2*2*2*2*2*2*2 +\
                                        thisCmd.reg*2*2*2*2*2*2*2*2 +\
                                        thisCmd.imm*2*2*2*2*2*2);             

enum compilationErrs 
        {
        NO_ERROR = 0,
        UNRECOGNISED_COMMAND = 1,
        MISSED_ARGUMENT = 2,
        TOO_MANY_ARGUMENTS = 3,
        WRITING_ERROR = 4,
        STRAY_OPEN_BRACKET = 5,
        STRAY_CLOSE_BRACKET = 6,
        EXTRA_BRACKETS = 7        
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

enum compilationErrs parseLine (struct Line* line);

struct errorInfo *compileCodeMain (struct errorInfo*, struct Text *codeText);

enum compilationErrs compileCode     (struct Text *codeText);

enum compilationErrs putToCode (char* cmd, 
                                char* line, double* arg);

enum compilationErrs isMemoryCommand (char** line, bool* isMemory);
enum compilationErrs isBracketStructureOk (char* oBracket, char* cBracket);

enum compilationErrs getArgument (char* line, double* argument,
                                  enum commands cmd, FILE* const asmHere);

char* skipCmd (char* str);

bool isMemoryCommand (char* line);

void printErrorInfo (struct errorInfo* pInfo);
void printSplitter ();

const double poisonProc = 0xFFFFFF;
static const char splitter[] = 
            "============================================================";

#endif
