#ifndef __JJC__SDL__LINE__H__
#define __JJC__SDL__LINE__H__

#include <SDL/SDL.h>
#include <transformSDL/SDL-Point.h>
#include <miniSTL/DynamicArray.h>

class SDL_Line {
private:
    // vector for point data
    DynamicArray<SDL_Point> __pt_Array;

    // SDL_Surface to draw to
    SDL_Surface* screen;

    // color of this line
    uint32_t color;

public:
    // default constructor
    SDL_Line(void) { ; }

    // constructor must be passed a Surface to draw to and a color to display
    SDL_Line(SDL_Surface* screen, uint32_t color);

    // optional constructor to build up the line using an array of SDL_Points
    SDL_Line(SDL_Surface* screen, uint32_t color, SDL_Point* pts, int numPts);

    // how many points the array is currently holding
    int lineSize(void);

    // access elements like you would in an array
    SDL_Point& operator[](const int index);

    SDL_Line& operator=(SDL_Line& __line);

    // put a point in __pt_Array
    void addPoint(SDL_Point sdlp);

    // get the associated SDL_Surface ptr
    SDL_Surface* getSurface(void);

    // get the color of this line
    uint32_t getColor(void);

    // set a new color for this line
    void setColor(uint32_t color);
};

SDL_Line::SDL_Line(SDL_Surface* screen, uint32_t color) {
    this->screen = screen;
    this->color  = color;
}

SDL_Line::SDL_Line(SDL_Surface* screen, uint32_t color, SDL_Point* pts, int numPts) {
    this->screen = screen;
    this->color  = color;

    for(int i = 0; i < numPts; i++) {
        __pt_Array.pushBack(pts[i]);
    }
}

int SDL_Line::lineSize(void) {
    return __pt_Array.arraySize();
}

SDL_Point& SDL_Line::operator[](const int index) {
    return __pt_Array[index];
}

SDL_Line& SDL_Line::operator=(SDL_Line& __line) {
    if(this != &__line) {
        color  = __line.getColor();
        screen = __line.getSurface();
        __pt_Array.clearSimple();

        int s = __line.lineSize();
        for(int i = 0; i < s; i++)
            __pt_Array.pushBack(__line[i]);
    }
    return *this;
}

void SDL_Line::addPoint(SDL_Point sdlp) {
    __pt_Array.pushBack(sdlp);
}

SDL_Surface* SDL_Line::getSurface(void) {
    return screen;
}

uint32_t SDL_Line::getColor(void) {
    return color;
}

void SDL_Line::setColor(uint32_t color) {
    this->color = color;
}

#endif // __JJC__SDL__LINE__H__
