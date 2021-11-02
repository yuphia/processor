#include "assFunctions.h"

int main()
{
    FILE* const code = fopen ("code+asm/code.txt", "rb");
    if (prepareAsm() == 0)
    {
        printf ("Couldn't open the output file with asm\n");
        return 1;
    }    

    MY_ASSERT (code != nullptr, "An error occurred while opening code file");
    if (code == nullptr)
    {
        printf ("Couldn't open the file with code\n");
        return 1;
    }

    struct Text codeText = {};

    fflush (stdout);
    getCode (code, &codeText);
    fclose (code);    

    compileCode (&codeText);

    free (codeText.textArray);
    freeArrayLines (codeText.lines);

    //printf ("mul = %d\n"
    //       "bit = %d\n",
    //        );

/*    cmdField thisCmd = {1, 0, 1, PUSH};
    printf ("mul = %d\n", thisCmd.cmd + thisCmd.mem*2*2*2*2*2*2 + 
                                        thisCmd.reg*2*2*2*2*2*2*2 + 
                                        thisCmd.imm*2*2*2*2*2); 

    printf ("bit = %d\n", thisCmd.cmd | 0b01000000*thisCmd.mem | 0b10000000*thisCmd.reg | 0b00100000*thisCmd.imm);*/

    return 0;
}


