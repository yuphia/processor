#include "assembler.h"

int main()
{
    FILE* const code = fopen ("code.txt", "rb");
    FILE* const asmHere = fopen ("asm.txt", "wb");

    MY_ASSERT (code != nullptr, "An error occurred while opening code file");
    MY_ASSERT (asmHere != nullptr, "An error occurred while opening assembler file");

    struct Text codeText = {};

    fflush (stdout);
    getCode (code, &codeText);
    
    compileCode (&codeText, asmHere);

    fclose (asmHere);
    fclose (code);

    free (codeText.textArray);
    freeArrayLines (codeText.lines);

    return 0;
}


