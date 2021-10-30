#include "assFunctions.h"

int main()
{
    FILE* const code = fopen ("code+asm/code.txt", "rb");
    fclose (fopen ("code+asm/asm.txt", "wb"));    
    MY_ASSERT (code != nullptr, "An error occurred while opening code file");
    
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


