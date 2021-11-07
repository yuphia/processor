#include "assFunctions.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf ("You forgot to put the asm and code files in the run setup\n"
                "You should use the command as follows\n"
                "%s input.asm output.bin\n", argv[0]);
        return 1;
    }

    FILE* const code = fopen (argv[1], "rb");    
    if (code == nullptr)
    {
        printf ("Couldn't open the file with code\n");
        return 1;
    }

    struct Text codeText = {};

    fflush (stdout);
    getCode (code, &codeText);
    fclose (code);    

    compileCode (&codeText, argv[2]);

    free (codeText.textArray);
    freeArrayLines (codeText.lines);

    return 0;
}


