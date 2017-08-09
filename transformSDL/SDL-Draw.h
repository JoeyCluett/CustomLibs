#ifndef __JJC__SDL__DRAW__H__
#define __JJC__SDL__DRAW__H__

#include <math.h>
#include <SDL/SDL.h>
#include <SDL/gfx/SDL_gfxPrimitives.h>

#include <transformSDL/SDL-Line.h>
#include <transformSDL/SDL-Point.h>

namespace XformSDL {

void drawLine(SDL_Line _line) {
    int s = _line.lineSize();

    if(s > 1) { // this will pass most of the time

        SDL_Point p1 = _line[0];
        SDL_Point p2;

        for(int i = 0; i < s-1; i++) {
            p2 = _line[i+1];

            // all of these floats get cast to signed 16 bit integers
            lineColor(_line.getSurface(), p1.x, p1.y, p2.x, p2.y, _line.getColor());
            p1 = p2;
        }
    }
}

void drawPolygon(SDL_Line _line) {
    int s = _line.lineSize();

    if(s > 2) {
        SDL_Point p1 = _line[0];
        SDL_Point p2;

        for(int i = 0; i < s; i++) {
            p2 = _line[(i+1) % s];

            lineColor(_line.getSurface(), p1.x, p1.y, p2.x, p2.y, _line.getColor());
            p1 = p2;
        }

    }
}

// applies translation to given line
void putTranslation(SDL_Line& _line, float dx, float dy) {
    int s = _line.lineSize();
    for(int i = 0; i < s; i++) {
        _line[i].x += dx;
        _line[i].y += dy;
    }
}

// applies rotation to given line
void putRotation(SDL_Line& _line, float rad) {
    int s = _line.lineSize();

    float sin_rad = sinf(rad);
    float cos_rad = cosf(rad);

    for(int i = 0; i < s; i++) {
        SDL_Point p = _line[i];

        float newx = p.x*cos_rad - p.y*sin_rad;
        float newy = p.x*sin_rad + p.y*cos_rad;

        p.x = newx;
        p.y = newy;

        _line[i] = p;
    }
}

// applies scaling to given line
void putScale(SDL_Line& _line, float scale) {
    int s = _line.lineSize();

    for(int i = 0; i < s; i++) {
        _line[i].x *= scale;
        _line[i].y *= scale;
    }
}

// applies transformation, rotation first
SDL_Line applyTransformRot(SDL_Line& _line, float dx, float dy, float rad) {
    float sin_rad = sinf(rad);
    float cos_rad = cosf(rad);

    int s = _line.lineSize();

    SDL_Line retLine(_line.getSurface(), _line.getColor());

    for(int i = 0; i < s; i++) {
        SDL_Point p = _line[i];

        float newx = p.x*cos_rad - p.y*sin_rad;
        float newy = p.x*sin_rad + p.y*cos_rad;

        p.x = newx + dx;
        p.y = newy + dy;

        retLine.addPoint(p);
    }

    return retLine;
}

// returns a line with the given transformation applied, translation first
SDL_Line applyTransformTra(SDL_Line& _line, float dx, float dy, float rad) {
    float sin_rad = sinf(rad);
    float cos_rad = cosf(rad);

    int s = _line.lineSize();

    SDL_Line retLine(_line.getSurface(), _line.getColor());

    for(int i = 0; i < s; i++) {
        SDL_Point p = _line[i];

        p.x += dx;
        p.y += dy;

        float newx = p.x*cos_rad - p.y*sin_rad;
        float newy = p.x*sin_rad + p.y*cos_rad;

        p.x = newx;
        p.y = newy;

        retLine.addPoint(p);
    }

    return retLine;
}

}

#endif // __JJC__SDL__DRAW__H__











