#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

class Player
{
public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
    int draw_frame;
    int floor;
   // int canBeWater;
    SDL_Surface *images[10];
    SDL_Surface *screen;

    Player(SDL_Surface *screen);
    void logic();
    void render();
    void jump();
    void die(int i);
    void setFloor(int i);
    virtual ~Player();

};

#endif // PLAYER_H
