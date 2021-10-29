#include "strlibMy.h"

int putsMy (char* str)
{
    MY_ASSERT (str != nullptr, "pointer to str equals nullptr");

    size_t counter = 0;
    printf ("%d", str [counter]);

    while (str [counter] != '\0')
    {
        //printf ("%d", str [counter]);
        putchar (str [counter]);
        counter++;
    }

    return (ferror (stdout)) ? EOF : 0;
}

int strcmpMy (const char* str1, const char* str2)
{
    MY_ASSERT (str1 != nullptr, "pointer to str1 equals nullptr");
    MY_ASSERT (str2 != nullptr, "pointer to str2 equals nullptr");

    while (*str1 == *str2 && *str1 != '\0')
    {
        //printf ("%d\n", ++testI);
        str1++, str2++;
    }

    return (int)(unsigned char)*str1 - (int)(unsigned char)*str2;
}

size_t strlenMy (const char *str)
{
    MY_ASSERT (str != nullptr, "pointer to str equals nullptr");

    size_t length = 0;
    for (; str [length] != '\0'; length++)
        ;

    return length;
}

const char* strchrMy_c (const char *str, int symbol)
{
    MY_ASSERT (str != nullptr, "pointer to str equals nullptr");

    for (; *str != '\0'; str++)
        if (*str == (char)symbol)
            return str;

    return NULL;
}

char* strchrMy (char *str, int symbol)
{
    MY_ASSERT (str != nullptr, "pointer to str equals nullptr");

    for (; *str != '\0'; str++)
        if (*str == (char)symbol)
            return str;

    if ((char) symbol == '\0')
        return str++;

    return NULL;
}

char* strcpyMy (char* destStr, const char* srcStr)
{
    MY_ASSERT (destStr != nullptr, "pointer to destStr equals nullptr");
    MY_ASSERT (srcStr  != nullptr, "pointer to srcStr  equals nullptr");

    size_t i = 0;
    for (; srcStr [i] != '\0';  i++)
        destStr [i] = srcStr[i];

    ++i;
    destStr [i] = srcStr [i];
    return destStr;
}

char* strncpyMy (char* destStr, const char* srcStr, size_t amount)
{
    MY_ASSERT (destStr != nullptr, "pointer to destStr equals nullptr");
    MY_ASSERT (srcStr  != nullptr, "pointer to srcStr  equals nullptr");

    if (destStr == nullptr || srcStr == nullptr)
    {
        errno = EINVAL;
        return destStr;
    }

    size_t i = 0;

    for (; i < amount;  i++)
    {
        destStr [i] = srcStr[i];

        if (srcStr [i] == '\0')
        {
            destStr [i] = '\0';
            return destStr;
        }
    }

    return destStr;
}

char *strcatMy (char *destStr, const char *srcStr)
{
    MY_ASSERT (destStr != nullptr, "pointer to destStr equals nullptr");
    MY_ASSERT (srcStr  != nullptr, "pointer to srcStr  equals nullptr");

    size_t destStr_len = strlenMy (destStr);
    size_t i = 0;

    for (; srcStr[i] != '\0'; i++)
        destStr [destStr_len + i] = srcStr[i];

    destStr [destStr_len + i + 1] = '\0';
    return destStr;
}

char *strncatMy (char *destStr, const char *srcStr, size_t amount)
{
    MY_ASSERT (destStr != nullptr, "pointer to destStr equals nullptr");
    MY_ASSERT (srcStr  != nullptr, "pointer to srcStr  equals nullptr");

    size_t destStr_len = strlenMy (destStr);
    size_t i = 0;

    for (; i < amount;  i++)
    {
        destStr [destStr_len + i] = srcStr[i];

        if (srcStr [i] == '\0')
        {
            destStr [destStr_len + i] = '\0';
            return destStr;
        }
    }

    return destStr;
}

char *fgetsMy (char *str, int maxSize, FILE* stream)
{
    if (str == nullptr || stream == nullptr || maxSize <= 0)
    {
        errno = EINVAL;
        return nullptr;
    }

    char character = '\0';
    char* str0 = str;

    printf ("%d, %ld", maxSize, str - str0);

    for (; str - str0 < maxSize; str++)
    {
        character = (char)getc (stream);

        putc (character, stdout);

        if (character == '\n' || character == EOF)
        {
            break;
        }
        *str = character;
    }

    if (character != EOF)
        *(str) = '\n';

    *(str + 1) = '\0';
    return (character == EOF) ? NULL : str;
}

char* strdupMy (const char* srcStr)
{
    MY_ASSERT (srcStr != nullptr, "pointer to srcStr equals nullptr");

    if (srcStr == NULL)
        return nullptr;

    char* strCpy = (char*)calloc (sizeof srcStr, sizeof (char));

    if (strCpy != nullptr)
    {
        size_t i = 0;
        for (; srcStr [i] != '\0';  i++)
            strCpy [i] = srcStr[i];

        ++i;
        strCpy [i] = srcStr [i];
    }

    return strCpy;
}

void printText (char* text[], size_t rows, FILE* outputFile)
{
    MY_ASSERT (text != nullptr, "pointer to text is equal to nullptr");

    for (size_t counter = 0; counter < rows;  counter++)
    {
        MY_ASSERT (text[counter] != nullptr, "pointer to text[counter] is equal to nullptr");

        fprintf (outputFile, "%s", text [counter]);
    }
}

