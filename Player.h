#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include "Floor.h"
#include "Enemy.h"

enum{
GROUND,
AIR,
FELL,
DEAD
};
class Player
{
private:
    void loadImages();
public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
  //  int draw_frame;
    int floor;
    int state;
    int input;
   // int canBeWater;
    SDL_Surface *images[10];
    SDL_Surface *screen;
    Mix_Chunk *jumpSfx;

    int frame_length;
    int frame_time_elapsed;

    Player(SDL_Surface *screen);
    void logic();
    void render();
    void jump();
    void die(int i);
    void setFloor(int i);
    virtual ~Player();
    void setInput(int input);
    void clearInput();
    bool playJump;
    void kill();
    bool isDead();
    void checkFloor(Floor *floor);    void checkCollision(Enemy *enemy);
    void initPosition();

};

#endif // PLAYER_H
