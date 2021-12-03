#include "disassembler/disassemblerCmds.h"

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

enum errCodes translateCode (unsigned char* code,
                             FILE* const disasmHere, size_t sizeOfCode)
{
    for (size_t ip = 0; ip < sizeOfCode; ip++)
    {
        enum errCodes tempErr = NO_ERROR;
        switch (*(code + ip))
        {
            case PUSH | 0b00100000: 
                   fprintf (disasmHere, "push %lg\n", *(double*)(code + ip + 1));
                   ip += 8;
                   break;

            case PUSH | 0b10000000:
                   fprintf (disasmHere, "push ");                   
                   
                   tempErr = translateRegister (*(code + ip + 1), disasmHere);
                   if (tempErr != NO_ERROR)
                       return tempErr;
                   
                   fprintf (disasmHere, "\n");               
                   ip++;
                   break;

            case (PUSH | 0b01000000) | 0b00100000:
                   fprintf (disasmHere, "push [%lg]\n", *(double*)(code + ip + 1));
                   ip += 8;
                   break;

            case ((PUSH | 0b01000000) | 0b10000000) | 0b00100000:
                   fprintf (disasmHere, "push [");

                   tempErr = translateRegister (*(code + ip + 1), disasmHere);
                   if (tempErr != NO_ERROR)
                       return tempErr;

                   fprintf (disasmHere, "+%lg]\n", *(double*)(code + ip + 2));
                   ip+=9;
                   break;

            case (PUSH | 0b01000000) | 0b10000000:
                   fprintf (disasmHere, "push [");

                   tempErr = translateRegister (*(code + ip + 1), disasmHere);
                   if (tempErr != NO_ERROR)
                       return tempErr;

                   fprintf (disasmHere, "]\n");
                   ip++;
                   break;

            case (PUSH | 0b00100000) | 0b10000000:
                   fprintf (disasmHere, "push ");
                   tempErr = translateRegister (*(code + ip + 1), disasmHere);

                   if (tempErr != NO_ERROR)
                       return tempErr;

                   fprintf (disasmHere, "+%lg\n", *(double*)(code + ip + 2));
                   ip+=9;
                   break;
        
            case POP:
                   fprintf (disasmHere, "pop\n");
                   break;

            case POP | 0b10000000:
                   fprintf (disasmHere, "pop ");
                   translateRegister (*(code + ip + 1), disasmHere); 
                   fprintf (disasmHere, "\n");
                   ip++;
                   break;              
            
            case (POP | 0b01000000) | 0b00100000:                   
                   fprintf (disasmHere, "pop [%lg]\n", *(double*)(code + ip + 1));
                   ip += 8;
                   break;

            case ((POP | 0b01000000) | 0b10000000) | 0b00100000:
                   fprintf (disasmHere, "pop [");

                   tempErr = translateRegister (*(code + ip + 1), disasmHere);
                   if (tempErr != NO_ERROR)
                       return tempErr;

                   fprintf (disasmHere, "+%lg]\n", *(double*)(code + ip + 2));
                   ip+=9;
                   break;

            case (POP | 0b01000000) | 0b10000000:
                   fprintf (disasmHere, "pop [");

                   tempErr = translateRegister (*(code + ip + 1), disasmHere);
                   if (tempErr != NO_ERROR)
                       return tempErr;

                   fprintf (disasmHere, "]\n");
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

            case PRNT:
                   fprintf (disasmHere, "print\n");
                   break;

            case IN:
                   fprintf (disasmHere, "in\n");
                   break;

            case CALL:
                   fprintf (disasmHere, "call %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case RET:
                   fprintf (disasmHere, "ret\n");
                   break;                   

            case JA:
                   fprintf (disasmHere, "ja %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case JAE:
                   fprintf (disasmHere, "jae %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case JB:
                   fprintf (disasmHere, "jb %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case JBE:
                   fprintf (disasmHere, "jbe %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case JE:
                   fprintf (disasmHere, "je %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case JNE:
                   fprintf (disasmHere, "jne %d\n", *(code + ip + 1));
                   ip++;
                   break;

            case DIV:
                   fprintf (disasmHere, "div\n");
                   break;

            case SUB:
                   fprintf (disasmHere, "sub\n");
                   break;

            case SQRT:
                   fprintf (disasmHere, "sqrt\n");
                   break;

            default:
                   return UNRECOGNISED_COMMAND;
                   break;
               }        
       } 

       return NO_ERROR;
}

enum errCodes translateRegister (int reg, FILE* const disasmHere)
{
    switch (reg)
    {
        case 1:
            fprintf (disasmHere, "ax");
            break;

        case 2:
            fprintf (disasmHere, "bx");
            break;

        case 3:
            fprintf (disasmHere, "cx");
            break;

        case 4:
            fprintf (disasmHere, "dx");
            break;

        default: 
            return UNKNOWN_REGISTER;
            break;
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
