#include "Enemy.h"

Enemy::Enemy(SDL_Surface *screen)
{
    this->screen = screen;
    this->images[0] = IMG_Load( "enemy/1.png" );
    this->images[1] = IMG_Load( "enemy/2.png" );
    this->images[2] = IMG_Load( "enemy/3.png" );
    this->x = -100;
    this->y = 200;
    this->acceleration=2;
    this->velocity=15;
    this->current_frame=0;
    srand(time(0));
}

Enemy::~Enemy()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
    SDL_FreeSurface( images[2] );
    SDL_FreeSurface( images[3] );
}

void Enemy::logic()
{
    x-=velocity;
    if(x< -100){
        if(rand()%100 < 1){

        x=1000;
        int randomAppear = rand()%3;
        if(randomAppear == 0){
            y = 200;
            velocity = 15;
        }else if(randomAppear == 1){
            y = 300;
            velocity = 18;
        }else{
            y = 200;
            velocity = 20;
        }


        }

    }

}

void Enemy::initPosition(){
 this->x = -101;

}

void Enemy::jump()
{
    velocity=-30;
}

void Enemy::render()
{
    SDL_Rect offset;

    offset.x = x - images[current_frame]->w/2;
    offset.y = y - images[current_frame]->h/2;

    SDL_BlitSurface( images[current_frame], NULL, screen, &offset );

    current_frame++;
    if(current_frame>2)
        current_frame=0;
}
