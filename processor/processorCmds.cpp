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

enum errCodes runCode (unsigned char* code, size_t sizeOfCode)
{
    struct stk<double> stkForProc = {};    
    ctorStk (&stkForProc, (double)LOWEST_DOUBLE, &dumpFunctionDouble);

    struct stk<int> stkForCalls = {};
    ctorStk (&stkForCalls, (int)LOWEST_INT, &dumpFunctionInt);

    struct processor proc = {{NAN, NAN, NAN, NAN}, stkForProc, stkForCalls, {}};
    fillOperativeNAN (proc.operative);
        
    for (size_t ip = 0; ip < sizeOfCode; ip++)
    {
        enum errCodes tempErr = NO_ERROR;

        double tempPop1 = NAN;
        double tempPop2 = NAN;
        double tempForRead = LOWEST_DOUBLE; 
        int tempForRet = -1;

        switch (*(code + ip))
        {
            case PUSH | 0b00100000:
                   pushStk<double> (&proc.stackProc, *(double*)(code + ip + 1));                
                   ip += 8;
                   break;

            case PUSH | 0b10000000:
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);

                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);                      
                       return tempErr;
                   }

                   ip++;
                   break;

            case (PUSH | 0b01000000) | 0b00100000:
                   pushStk<double> (&proc.stackProc, proc.operative[(int)*(double*)(code + ip + 1)]);
                   ip += 8;
                   break;

            case ((PUSH | 0b01000000) | 0b10000000) | 0b00100000:
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);
                   pushStk<double> (&proc.stackProc, *(double*)(code + ip + 2));
                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);                      
                       return tempErr;
                   }

                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);
                   
                   pushStk<double> (&proc.stackProc, 
                                     proc.operative[(int)(tempPop1 + tempPop2)]);                  

                   ip+=9;
                   break;

            case (PUSH | 0b01000000) | 0b10000000:
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);

                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);                                           
                       return tempErr;
                   }

                   popStk<double> (&proc.stackProc, &tempPop1);

                   pushStk<double> (&proc.stackProc, proc.operative[(int)tempPop1]);                  

                   ip++;
                   break;

            case (PUSH | 0b00100000) | 0b10000000:
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);

                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);                      
                       return tempErr;
                   }

                   pushStk<double> (&proc.stackProc, *(double*)(code + ip + 2));                                   
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);

                   pushStk<double> (&proc.stackProc, tempPop1 + tempPop2);
    
                   ip+=9;
                   break;

            case POP:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   break;

            case POP | 0b10000000:
                   tempErr = popStkToRegister ((enum registersEnum)*(code + ip + 1), &proc); 
                   ip++;
                   break;

            case (POP | 0b01000000) | 0b00100000:
                   popStk<double> (&proc.stackProc, &proc.operative[(int)*(double*)(code + ip + 1)]);
                   ip += 8;
                   break;

            case ((POP | 0b01000000) | 0b10000000) | 0b00100000:
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);
                   pushStk<double> (&proc.stackProc, *(double*)(code + ip + 2));
                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);
                       return tempErr;
                   }
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);
                   
                   popStk<double> (&proc.stackProc, 
                                     &proc.operative[(int)(tempPop1 + tempPop2)]);                  

                   ip+=9;
                   break;

            case (POP | 0b01000000) | 0b10000000: 
                   tempErr = pushStkFromRegister ((enum registersEnum)*(code + ip + 1), &proc);

                   if (tempErr != NO_ERROR)
                   {
                       dtorStk<int> (&stkForCalls);
                       dtorStk<double> (&stkForProc);
                       return tempErr;
                   }
                   popStk<double> (&proc.stackProc, &tempPop1);

                   popStk<double> (&proc.stackProc, &proc.operative[(int)tempPop1]);                  

                   ip++;
                   break;

            case JMP:
                   ip = *(code + ip + 1);
                   ip--;                   
                   break;

            case ADD:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);

                   pushStk<double> (&proc.stackProc,
                                    tempPop1 + tempPop2);
                   break;

            case DIV:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);

                   pushStk<double> (&proc.stackProc,
                                    tempPop1 / tempPop2);
                   break;

            case SUB:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);

                   pushStk<double> (&proc.stackProc,
                                    tempPop1 - tempPop2);
                   break;

            case MUL:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   popStk<double> (&proc.stackProc, &tempPop2);

                   pushStk<double> (&proc.stackProc,
                                    tempPop1 * tempPop2);
                   break;

            case HALT:
                   dtorStk<int> (&proc.stackCalls);
                   dtorStk<double> (&proc.stackProc);
                   
                   return NO_ERROR;
                   break;

            case PRNT:
                   popStk<double> (&proc.stackProc, &tempPop1);
                   printf ("%lg\n", tempPop1);
                   break;

            case IN:
                   scanf ("%lg", &tempForRead);

                   if (tempForRead == LOWEST_DOUBLE)                                          
                   {
                       dtorStk<int> (&proc.stackCalls);
                       dtorStk<double> (&proc.stackProc);                  
                       return FALSE_READ;                                      
                   }
                   pushStk<double> (&proc.stackProc, tempForRead);
                   break;                  

            case CALL:
                   pushStk<int> (&proc.stackCalls, ip+1);
                   ip = *(code + ip + 1);
                   ip--;                   
                   break;

            case RET:                    
                   popStk<int> (&proc.stackCalls, &tempForRet);
                   ip = (size_t)tempForRet;
                   break;

            case JA: 
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   if (tempPop1 > tempPop2)
                   {
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;

            case JAE:
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   if (tempPop1 >= tempPop2)
                   {
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;
                
            case JB:
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   if (tempPop1 < tempPop2)
                   {
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;

            case JBE:
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   if (tempPop1 <= tempPop2)
                   {
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;

            case JE:
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   if (tempPop1 - tempPop2 < 1e-10 && tempPop2 - tempPop1 > -1e-10)
                   {
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;

            case JNE:
                   popStk<double>(&proc.stackProc, &tempPop1);
                   popStk<double>(&proc.stackProc, &tempPop2);

                   printf ("jne = %d", tempPop1 - tempPop2 >= 1e-10 || tempPop2 - tempPop1 <= -1e-10);
                   if (tempPop1 - tempPop2 >= 1e-10 || tempPop2 - tempPop1 <= -1e-10)
                   {
                       $
                       ip = *(code + ip + 1);
                       ip--;
                   }
                   else
                       ip++;

                   break;

            default:                  
                   printf ("command = %d\n", *(code+ip)); 
                   dtorStk<int> (&proc.stackCalls);
                   dtorStk<double> (&proc.stackProc);
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

        case FALSE_READ:
            printf ("False read\n");
            break;

        case WRONG_RET:
            printf ("Ret w/o calls\n");
            break;

        default:
            printf ("Error in errors lol\n");
    }
}

void fillOperativeNAN (double* operative)
{
    MY_ASSERT (operative != nullptr, "pointer to operative is equal to nullptr\n");

    for (size_t i = 0; i < OPERATIVE_SIZE; i++)
    {
        operative[i] = NAN;       
    } 
}

enum errCodes pushStkFromRegister (enum registersEnum reg, struct processor *proc)
{
    switch (reg)
    {
        case ax:
            pushStk<double> (&(proc->stackProc), proc->regs.ax);
            break;

        case bx:
            pushStk<double> (&(proc->stackProc), proc->regs.bx);
            break;

        case cx:
            pushStk<double> (&(proc->stackProc), proc->regs.cx);
            break;

        case dx:
            pushStk<double> (&(proc->stackProc), proc->regs.dx);
            break;

        default:
            return UNKNOWN_REGISTER;
    }

    return NO_ERROR;
}

enum errCodes popStkToRegister (enum registersEnum reg, struct processor *proc)
{
    double tempForPop = NAN;
    switch (reg)
    {
        case ax:
            popStk<double> (&(proc->stackProc), &tempForPop);
            proc->regs.ax = (enum registersEnum)tempForPop;             
            break;

        case bx:
            popStk<double> (&(proc->stackProc), &tempForPop);
            proc->regs.bx = (enum registersEnum)tempForPop;     
            break;

        case cx:
            popStk<double> (&(proc->stackProc), &tempForPop);
            proc->regs.cx = (enum registersEnum)tempForPop;
            break;

        case dx:
            popStk<double> (&(proc->stackProc), &tempForPop);
            proc->regs.dx = (enum registersEnum)tempForPop;
            break;

        default:
            return UNKNOWN_REGISTER;
    }

    return NO_ERROR;
}

#endif
