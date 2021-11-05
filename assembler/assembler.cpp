#include "assFunctions.h"

int main()
{
    FILE* const code = fopen ("code+asm/code.txt", "rb");    

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

    return 0;
}


