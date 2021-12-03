#ifndef DISASSEMBLER_CMDS_H

#define DISASSEMBLER_CMDS_H 1

#include "sort/sort.h"
#include "strlibMy/strlibMy.h"
#include "fileInputTreatment/fileInputTreatment.h"
#include "commands/commands.h"
#include "myAssert/myAssert.h"

#define $ printf ("line = %d\n", __LINE__);

enum errCodes
    {
    NO_ERROR = 0,
    UNRECOGNISED_COMMAND = 1,
    UNKNOWN_REGISTER = 2
    };

unsigned char* getCode (FILE* const code, size_t* sizeOfCode);
enum errCodes translateCode (unsigned char* code,
                             FILE* const disasmHere, size_t sizeOfCode);
enum errCodes translateRegister (int reg, FILE* const disasmHere);
void printErr (enum errCodes err);
#endif

