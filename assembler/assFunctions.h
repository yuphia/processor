#ifndef ASS_FUNCTIONS_H

#define ASS_FUNCTIONS_H 1

#include "sort.h"
#include "strlibMy.h"
#include "fileInputTreatment.h"
#include "commands.h"
#include "myAssert.h"

#define WRITE(cmd)\
        char thisCmdN = cmd;\
        fwrite (&thisCmdN, sizeof(char), 1, asmHere);

#define WRITE_REGISTER()\
        {\
            char regTemp = (char)reg;\
            fwrite (&regTemp, sizeof(char), 1, asmHere);\
        }

#define FILL_FIELD_AND_WRITE()\
            struct cmdField thisCmd = {isRegister, isMemory, isImmidiate, cmd};\
            WRITE (thisCmd.cmd + (((thisCmd.cmd | 0b01000000*thisCmd.mem) \
                                               | 0b10000000*thisCmd.reg) \
                                               | 0b00100000*thisCmd.imm))            

#define $ printf ("line = %d\n", __LINE__);\
          fflush (stdout);

const size_t START_LABELS_SIZE = 1;

enum compilationErrs 
        {
        NO_ERROR = 0,
        UNRECOGNISED_COMMAND = 1,
        MISSED_ARGUMENT = 2,
        TOO_MANY_ARGUMENTS = 3,
        WRITING_ERROR = 4,
        STRAY_OPEN_BRACKET = 5,
        STRAY_CLOSE_BRACKET = 6,
        EXTRA_BRACKETS = 7,
        WRONG_REG_ERROR = 8,
        FORBIDDEN_ARGUMENT = 9,
        OUTPUT_FILE_ERROR = 10,
        RUBBISH_IN_LINE = 11,        
        NO_LABEL_IN_JUMP = 12,
        NOT_A_LABEL = 13,
        UNKNOWN_LABEL = 14, 
        TEMP_MEMORY_ERROR = 15
        };

enum Reg
        {
        AX = 1,
        BX = 2,
        CX = 3,
        DX = 4,
        WRONG_REG = 5
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

struct label
        {
        char* label;
        size_t labelPointsTo;        
        };

void getCode (FILE* const code, struct Text *codeText);

enum compilationErrs parseLine (struct Line* line, FILE* const asmHere,
                                size_t currLine, struct label ***labels,
                                bool isWriteAllowed, 
                                size_t* currLabel, size_t* sizeOfLabels);

struct errorInfo *compileCodeMain (struct errorInfo*, struct Text *codeText, 
                                   char* codeFileName);

enum compilationErrs compileCode     (struct Text *codeText, char* codeFileName);

enum compilationErrs putToCode (char* cmd, char* line, double* arg, 
                                FILE* const asmHere, size_t currLine,
                                struct label ***labels, bool isWriteAllowed,
                                size_t* currLabel, size_t* sizeOfLabels);

enum compilationErrs isMemoryCommand (char** line, bool* isMemory);
enum compilationErrs isBracketStructureOk (char* oBracket, char* cBracket);

enum compilationErrs getArgument (char* line, double* argument,
                                  enum commands cmd, FILE* const asmHere,
                                  bool isMemAllowed, bool isRegAllowed, bool isImmAllowed,
                                  bool isNoArgAllowed);

enum compilationErrs isImmRegDetection (char* line, bool* isRegister, 
                                        bool* isImmidiate,
                                        double* arg, enum Reg* reg);

enum Reg detectRegister (char* regName);

char* skipCmd (char* str);

bool isMemoryCommand (char* line);

char* jumpToLastSpace (char* line);

bool isComment (char* line);
enum compilationErrs checkCmdForComment (char* line, bool isCmdInside);

bool isRegOk (char* regName);

void printErrorInfo (struct errorInfo* pInfo);
void printSplitter ();

const double poisonProc = 0xFFFFFF;
static const char splitter[] = 
            "============================================================";

bool prepareAsm();

enum compilationErrs insertLabel (char* line, struct label **labels, 
                                  enum commands cmd, FILE* const asmHere, 
                                  size_t sizeOfLabels);

enum compilationErrs detectLabel (char* line, size_t whichLine,
                                  struct label ***labels, size_t currLabel,
                                  size_t *sizeOfLabels);

bool isLabel (char* line);
bool callocTheInside (struct label** labels);
void removeSpaces (char** line);
int countSpacesInFront (char* line);

void freeAllLabels (struct label** labels, size_t sizeOfLabels);
#endif
