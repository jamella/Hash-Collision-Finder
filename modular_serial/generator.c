#include<stdlib.h>
#include<time.h>
#include<math.h>

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

unsigned long long int calculate_iterations(int desired_bytes)
{
    unsigned long long int result = 1;
    
    for (int i = 1; i <= ((desired_bytes * 4) / 2); i++){
        result *= 2; 
    }

    return result;
}
