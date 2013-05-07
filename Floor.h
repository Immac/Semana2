#ifndef FLOOR_H
#define FLOOR_H
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

class Floor
{
    public:
        Floor(SDL_Surface *screen, bool canBeWater);
        void logic();
        void render();
                int x;
                   int y;
                     int state;
        virtual ~Floor();
        void initPosition();
        void goNextTo(Floor *suelo);
        void setNextFloor(Floor *nextFloor);
        Floor *nextFloor;
    protected:
    private:
        bool canBeWater;


        SDL_Surface *image[2];
        SDL_Surface *screen;
};

#endif // FLOOR_H
