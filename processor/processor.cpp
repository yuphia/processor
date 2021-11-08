#include "processorCmds.h"

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf ("You forgot to put filenames in the setup command.\n"
                "Please use the setup as follows.\n"
                "%s input.bin\n", argv[0]);
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

    enum errCodes errCode = NO_ERROR;

    errCode = runCode (machineCode, sizeOfCode);
    
    printErr (errCode);

    free (machineCode);
    return 0;
}
