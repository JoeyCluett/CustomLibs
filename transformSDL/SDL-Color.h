#ifndef __JJC__SDL__COLOR__H__
#define __JJC__SDL__COLOR__H__

#include <SDL/SDL.h>

uint32_t getSolidFromPixel(SDL_Surface* screen, uint32_t sdl_color) {
    uint8_t r, g, b;
    SDL_GetRGB(sdl_color, screen->format, &r, &g, &b);
    uint32_t ret_color = 0x00000000;

    // position red
    ret_color |= r;
    ret_color = ret_color << 8;

    // position green
    ret_color |= g;
    ret_color = ret_color << 8;

    // position blue
    ret_color |= b;
    ret_color = ret_color << 8;

    // full alpha every time
    ret_color |= 0xFF;

    return ret_color;
}

#endif // __JJC__SDL__COLOR__H__
