#ifndef PROCESSOR_CMDS_H

#define PROCESSOR_CMDS_H 1

#include "sort.h"
#include "strlibMy.h"
#include "fileInputTreatment.h"
#include "commands.h"
#include "myAssert.h"
#include "ultimateGuard.h"

enum errCodes
    {
    NO_ERROR = 0,
    UNRECOGNISED_COMMAND = 1,
    UNKNOWN_REGISTER = 2
    };

struct registers
    {
    double ax;
    double bx;
    double cx;
    double dx;
    };

struct processor
    {
    struct registers regs;

    struct stk<double> stackProc;

    double operative [1600];
    };

unsigned char* getCode (FILE* const code, size_t* sizeOfCode);
enum errCodes runCode (unsigned char* code,
                             FILE* const disasmHere, size_t sizeOfCode);
    
void printErr (enum errCodes err);
#endif

