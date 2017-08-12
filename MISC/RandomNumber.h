#ifndef __JJC__RANDOM__NUMBER__H__
#define __JJC__RANDOM__NUMBER__H__

#include <time.h>
#include <stdlib.h>

// this function also performs initialization of the random number generator
int getRandomNumber(void) {
    static int i = 0;
    if(i == 0) {
        srand(time(NULL));
        i = 1;
    }
    return rand();
}

#endif // __JJC__RANDOM__NUMBER__H__
