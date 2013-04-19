#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

class Background
{
    public:
        Background(SDL_Surface *screen);
        void logic();
        void render();
        virtual ~Background();
    protected:
    private:
    int x;
    SDL_Surface *image;
    SDL_Surface *screen;
};

#endif // BACKGROUND_H
