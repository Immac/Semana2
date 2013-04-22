#include "Player.h"


Player::Player(SDL_Surface *screen)
{
    this->screen = screen;
    this->images[0] = IMG_Load( "player/1.png" );
    this->images[1] = IMG_Load( "player/2.png" );
    this->images[2] = IMG_Load( "player/3.png" );
    this->images[3] = IMG_Load( "player/4.png" );
    this->images[4] = IMG_Load( "player/5.png" );
    this->images[5] = IMG_Load( "player/perder01.png" );
    this->images[6] = IMG_Load( "player/perder02.png" );
    this->images[7] = IMG_Load( "player/perder03.png" );
    this->images[8] = IMG_Load( "player/perder04.png" );
    this->images[9] = IMG_Load( "player/perder05.png" );
    this->x = 200;
    this->y = 0;
    this->acceleration = 2;
    this->velocity = 0;
    this->current_frame = 0;
    this->draw_frame = 0;
}

Player::~Player()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
    SDL_FreeSurface( images[2] );
    SDL_FreeSurface( images[3] );
}

void Player::logic()
{
    y+=velocity;
    velocity+=acceleration;
    if(y>=500-images[draw_frame]->w/2)
    {
        y=500-images[draw_frame]->w/2;
        velocity=0;
    }
}

void Player::jump()
{
    if(y>=500-images[draw_frame]->w/2)
    {
       velocity=-30;
    }

}

void Player::render()
{
    SDL_Rect offset;

    offset.x = x - images[draw_frame]->w/2 - (images[0]->w - images[draw_frame]->w)/2;
    offset.y = y - images[draw_frame]->h/2 + (images[0]->h - images[draw_frame]->h)/1;

    if(y>=500-images[draw_frame]->w/2 || draw_frame > 4 )
    {
      SDL_BlitSurface( images[draw_frame], NULL, screen, &offset );
    } else {
        SDL_BlitSurface( images[4], NULL, screen, &offset );
    }

    current_frame++;
    if(current_frame>5)
        current_frame=0;
        draw_frame = current_frame/2;
}

void Player::die(int i){
    velocity=0;
    draw_frame = i + 5;
  }
