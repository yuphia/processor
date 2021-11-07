#include "disassemblerCmds.h"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf ("You forgot to put filenames\n");
        return 1;
    }    

    FILE* const asmFromHere = fopen (argv[1], "rb");
    if (asmFromHere == nullptr)
    {
        printf ("Couldn't open the file with the assembler code\n");
        return 1;
    }

    size_t sizeOfCode = 0;
    unsigned char* machineCode = getCode (asmFromHere, &sizeOfCode);
    fclose (asmFromHere);

    FILE* const disasmHere = fopen (argv[2], "w");
    enum errCodes errCode = translateCode (machineCode, disasmHere, sizeOfCode);

    printErr (errCode);

    fclose (disasmHere);

    free (machineCode);
    return 0;   
}
