#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>
#include <ctime>
#include  <cmath>
class Enemy
{
public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
    SDL_Surface *images[3];
    SDL_Surface *screen;

    Enemy(SDL_Surface *screen);
    void logic();
    void render();
    void jump();
    virtual ~Enemy();
    void initPosition();
};

#endif // ENEMY_H
