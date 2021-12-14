#include "ultimateGuard/ultimateGuard.h"

void prepareLogs ()
{
    FILE* const temp = fopen ("log.txt", "w");

    MY_ASSERT (temp != nullptr, "Couldn't prepare logs (open the log.txt)");
    fclose (temp);
}

hash_t rotl (hash_t n)
{
    unsigned d = 13;
    n *= d;
    return (n << d)|(n >> (32 - d));
}
