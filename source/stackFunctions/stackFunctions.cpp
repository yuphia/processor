#include "stackFunctions/stackFunctions.h"

size_t updDumpCounter()
{
    static size_t dumpCounter = 0;

    dumpCounter++;
    return dumpCounter;
}

void dumpFunctionInt (struct stk<int>* stk, size_t i, FILE* const logFileConst)
{
    fprintf (logFileConst,  "buffer[%zu] = %d\n", i, *(int*)((unsigned char*)stk->buffer + i*sizeof(int) + sizeof (canary_t)));
}

void dumpFunctionDouble (struct stk<double>* stk, size_t i, FILE* const logFileConst)
{
    fprintf (logFileConst,  "buffer[%zu] = %lg\n", i, *(double*)((unsigned char*)stk->buffer + i*sizeof(double) + sizeof (canary_t)));
}
