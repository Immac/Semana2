#include "Floor.h"
#include <cmath>
#include <ctime>

Floor::Floor(SDL_Surface *screen,bool canBeWater)
{
    this->screen = screen;
    this->image[0] = IMG_Load( "enemy/tierra.png");
    this->image[1] = IMG_Load( "enemy/agua.png");
    this->x = 0;
    this->y =450;
    this->canBeWater =canBeWater;
    this->state = 0;
    srand(time(0));
    if(canBeWater){
    this->state = ( rand() %2 );
    }
}

void Floor::logic(){
x-=10;

}

void Floor::render(){

 SDL_Rect offset;


    if(x< -image[state]->w){
        x=1000;
        if(canBeWater){
        this->state = ( rand() %2 );
        }
    }

    offset.x = x;
    offset.y = 450 - 12;

SDL_BlitSurface( image[state], NULL, screen, &offset );

/*
    offset.x = x+image->w;
    offset.y = 450 - 12;

    SDL_BlitSurface( image, NULL, screen, &offset );
*/

}

Floor::~Floor()
{

   SDL_FreeSurface( image[0] );
   SDL_FreeSurface( image[1] );
}
