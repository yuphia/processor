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

    /*cmdField thisCmd = {0, 0, 1, PUSH};
    printf ("cmd = %d", thisCmd.cmd + thisCmd.mem*2*2*2*2*2*2*2 + 
                                      thisCmd.reg*2*2*2*2*2*2*2*2 + 
                                      thisCmd.imm*2*2*2*2*2*2); */

    return 0;
}


