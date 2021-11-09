#ifndef PROCESSOR_CMDS_H

#define PROCESSOR_CMDS_H 1                 

#include "sort.h"
#include "strlibMy.h"
#include "fileInputTreatment.h"
#include "commands.h"
#include "myAssert.h"
#include "ultimateGuard.h"

const size_t OPERATIVE_SIZE = 1600;

const double LOWEST_DOUBLE = -2147483648;
const int LOWEST_INT = -2147483646;

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
    double ax;
    double bx;
    double cx;
    double dx;
    };

enum registersEnum
    {
    ax = 1,
    bx = 2,
    cx = 3,
    dx = 4   
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

//double abs (double n);
#endif

