#ifndef __JJC__SDL__POINT__H__
#define __JJC__SDL__POINT__H__

struct SDL_Point {
    float x;
    float y;

    SDL_Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    SDL_Point(void) {
        ;
    }
};

#endif // __JJC__SDL__POINT__H__
