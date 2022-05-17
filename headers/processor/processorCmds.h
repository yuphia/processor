#ifndef PROCESSOR_CMDS_H

#define PROCESSOR_CMDS_H 1

#include "sort/sort.h"
#include "strlibMy/strlibMy.h"
#include "fileInputTreatment/fileInputTreatment.h"
#include "commands/commands.h"
#include "myAssert/myAssert.h"
#include "stackFunctions/stackFunctions.h"
#include "ultimateGuard/ultimateGuard.h"

const size_t OPERATIVE_SIZE = 1600;


enum errCodes
    {
    NO_ERROR = 0,
    UNRECOGNISED_COMMAND = 1,
    UNKNOWN_REGISTER = 2,
    FALSE_READ = 3,
    WRONG_RET = 4,
    NEGATIVE_SQRT = 5
    };

struct registers
    {
    double* registers;
    size_t amount;
    /*double ax;
    double bx;
    double cx;
    double dx;*/
    };

enum registersEnum
    {
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3
    };

struct processor
    {
    struct registers regs;

    struct stk<double> stackProc;

    struct stk<int> stackCalls;

    double operative [OPERATIVE_SIZE];
    };

unsigned char* getCode (FILE* const code, size_t* sizeOfCode);
enum errCodes runCode (unsigned char* code, size_t sizeOfCode);

void printErr (enum errCodes err);

void fillOperativeNAN (double* operative);

enum errCodes pushStkFromRegister (enum registersEnum reg, struct processor *proc);

enum errCodes popStkToRegister (enum registersEnum reg, struct processor *proc);

void regsNAN (struct registers * regs);



//double abs (double n);
#endif

