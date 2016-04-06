#include<stdlib.h>
#include<time.h>

#include"generator.h"

_Bool seed_generator()
{
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
        return false;
    } else {
        srandom(ts.tv_nsec ^ ts.tv_sec);
        return true;
    }
}

long int generate_number()
{
    return random();
}
