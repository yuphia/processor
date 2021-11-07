#ifndef PROCESSOR_CMDS_CPP

#define PROCESSOR_CMDS_CPP 1

#include "processorCmds.h"

unsigned char* getCode (FILE* const code, size_t* sizeOfCode)
{
    MY_ASSERT (code != nullptr, "A mistake happened while opening code file\n");


    fseek(code, 0L, SEEK_END);
    *sizeOfCode = (size_t)ftell(code);
    fseek(code, 0L, SEEK_SET);

    unsigned char* pointerToMachineCode =
            (unsigned char*)calloc (*sizeOfCode, sizeof(unsigned char));

    fread (pointerToMachineCode, sizeof(unsigned char), *sizeOfCode, code);

    return pointerToMachineCode;
}

enum errCodes runCode (unsigned char* code,
                             FILE* const disasmHere, size_t sizeOfCode)
{
    struct stk<double> stackForProc = {};
    ctorStk (&stackForProc, (double)NAN, &dumpFunctionDouble);

    struct processor proc = {{NAN, NAN, NAN, NAN}, stackForProc, {}};
        
    for (size_t ip = 0; ip < sizeOfCode; ip++)
    {
        //enum errCodes tempErr = NO_ERROR;
        switch (*(code + ip))
        {
            case PUSH | 0b00100000:
                   fprintf (disasmHere, "push %lg\n", *(double*)(code + ip + 1));
                   ip += 8;
                   break;

            case PUSH | 0b10000000:
                   fprintf (disasmHere, "push ");

                   fprintf (disasmHere, "\n");
                   ip++;
                   break;

            case (PUSH | 0b01000000) | 0b00100000:
                   fprintf (disasmHere, "push [%lg]", *(double*)(code + ip + 1));
                   ip += 8;
                   break;

            case ((PUSH | 0b01000000) | 0b10000000) | 0b00100000:
                   fprintf (disasmHere, "push [");

                   fprintf (disasmHere, "+%lg]\n", *(double*)(code + ip + 2));
                   ip+=9;
                   break;

            case (PUSH | 0b01000000) | 0b10000000:
                   fprintf (disasmHere, "push [");

                   fprintf (disasmHere, "]\n");
                   ip++;
                   break;

            case (PUSH | 0b00100000) | 0b10000000:
                   fprintf (disasmHere, "push ");

                   fprintf (disasmHere, "+%lg\n", *(double*)(code + ip + 2));
                   ip+=9;
                   break;

            case POP:
                   fprintf (disasmHere, "pop\n");
                   break;

            case POP | 0b10000000:
                   fprintf (disasmHere, "pop ");
                   fprintf (disasmHere, "\n");
                   ip++;
                   break;

            case JMP:
                   fprintf (disasmHere, "jmp %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case ADD:
                   fprintf (disasmHere, "add\n");
                   break;

            case MUL:
                   fprintf (disasmHere, "mul\n");
                   break;

            case HALT:
                   fprintf (disasmHere, "hlt\n");
                   break;

            default:
                   return UNRECOGNISED_COMMAND;
                   break;
               }
       }

       return NO_ERROR;
}

void printErr (enum errCodes err)
{
    switch (err)
    {
        case UNRECOGNISED_COMMAND:
            printf ("Unrecognised command\n");
            break;

        case UNKNOWN_REGISTER:
            printf ("Unknown register\n");
            break;

        case NO_ERROR:
            break;

        default:
            printf ("Error in errors lol\n");
    }
}
#endif
