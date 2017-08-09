#ifndef __JJC__SDL__FIELD__H__
#define __JJC__SDL__FIELD__H__

/*
    Always assumes you are using a 32-bit SDL_Surface
*/

class SDL_Field {
public:
    // constructor allocates sufficient memory
    SDL_Field(int width, int height);

    // destructor deallocates memory associated with field
    ~SDL_Field(void);

    // draw a rectangle onto this field, r=0 fills the entire field
    void fillRect(SDL_Rect* r, uint32_t color);

    // guess what these do
    int getHeight(void);
    int getWidth(void);

private:
    // memory associated with field
    uint32_t* __bkgd_f = 0;

    int width, height;

    // performs bounds checking on every pixel to be drawn
    void fillPixel(int x, int y, uint32_t color);

};

SDL_Field::SDL_Field(int width, int height) {
    __bkgd_f = new uint32_t[width * height];

    this->height = height;
    this->width  = width;
}

SDL_Field::~SDL_Field(void) {
    if(__bkgd_f)
        delete[] __bkgd_f;
}

void SDL_Field::fillPixel(int x, int y, uint32_t color) {
    if(!(x < 0 || y < 0)) {
        if(!(x >= width || y >= height)) {
            __bkgd_f[y*width + x] = color;
        }
    }
}

#endif // __JJC__SDL__FIELD__H__
