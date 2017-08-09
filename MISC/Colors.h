#ifndef __JJC__COLORS__H__
#define __JJC__COLORS__H__

#include <SDL/SDL.h>
#include <transformSDL/SDL-Color.h>

#include <stdlib.h>
#include <time.h>

#define CP_TO_GFX(c) c = getSolidFromPixel(screen, c)

class ColorPallette {
public:
    ColorPallette(SDL_Surface* screen);

    uint32_t white;
    uint32_t silver;
    uint32_t grey;
    uint32_t black;
    uint32_t red;
    uint32_t maroon;
    uint32_t yellow;
    uint32_t olive;
    uint32_t lime;
    uint32_t green;
    uint32_t aqua;
    uint32_t teal;
    uint32_t blue;
    uint32_t navy;
    uint32_t fuschia;
    uint32_t purple;

    void convertColorsToGfxMode(void);
    uint32_t getRandomColor(void);

private:
    SDL_Surface* screen;
};

ColorPallette::ColorPallette(SDL_Surface* screen) {
    this->screen = screen;
    SDL_PixelFormat* sdlf = screen->format;

    white   = SDL_MapRGB(sdlf, 0xFF, 0xFF, 0xFF);
    silver  = SDL_MapRGB(sdlf, 0xC0, 0xC0, 0xC0);
    grey    = SDL_MapRGB(sdlf, 0x80, 0x80, 0x80);
    black   = SDL_MapRGB(sdlf, 0x00, 0x00, 0x00);
    red     = SDL_MapRGB(sdlf, 0xFF, 0x00, 0x00);
    maroon  = SDL_MapRGB(sdlf, 0x80, 0x00, 0x00);
    yellow  = SDL_MapRGB(sdlf, 0xFF, 0xFF, 0x00);
    olive   = SDL_MapRGB(sdlf, 0x80, 0x80, 0x00);
    lime    = SDL_MapRGB(sdlf, 0x00, 0xFF, 0x00);
    green   = SDL_MapRGB(sdlf, 0x00, 0x80, 0x00);
    aqua    = SDL_MapRGB(sdlf, 0x00, 0xFF, 0xFF);
    teal    = SDL_MapRGB(sdlf, 0x00, 0x80, 0x80);
    blue    = SDL_MapRGB(sdlf, 0x00, 0x00, 0xFF);
    navy    = SDL_MapRGB(sdlf, 0x00, 0x00, 0x80);
    fuschia = SDL_MapRGB(sdlf, 0xFF, 0x00, 0xFF);
    purple  = SDL_MapRGB(sdlf, 0x80, 0x00, 0x80);

    srand(time(NULL));
}

void ColorPallette::convertColorsToGfxMode(void) {
    CP_TO_GFX(white);
    CP_TO_GFX(silver);
    CP_TO_GFX(grey);
    CP_TO_GFX(black);
    CP_TO_GFX(red);
    CP_TO_GFX(maroon);
    CP_TO_GFX(yellow);
    CP_TO_GFX(olive);
    CP_TO_GFX(lime);
    CP_TO_GFX(green);
    CP_TO_GFX(aqua);
    CP_TO_GFX(teal);
    CP_TO_GFX(blue);
    CP_TO_GFX(navy);
    CP_TO_GFX(fuschia);
    CP_TO_GFX(purple);
}

uint32_t ColorPallette::getRandomColor(void) {
    static uint32_t colorArray[16];
    static int doCopy = 0;
    if(doCopy == 0) {
        colorArray[0]  = white;
        colorArray[1]  = silver;
        colorArray[2]  = grey;
        colorArray[3]  = black;
        colorArray[4]  = red;
        colorArray[5]  = maroon;
        colorArray[6]  = yellow;
        colorArray[7]  = olive;
        colorArray[8]  = lime;
        colorArray[9]  = green;
        colorArray[10] = aqua;
        colorArray[11] = teal;
        colorArray[12] = blue;
        colorArray[13] = navy;
        colorArray[14] = fuschia;
        colorArray[15] = purple;
        doCopy = 1;
    }

    int r_index = rand() % 16;
    return colorArray[r_index];
}

#endif // __JJC__COLORS__H__





