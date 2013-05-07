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
    this->nextFloor = NULL;
    }
}

void Floor::logic(){
x-=15;

}

void Floor::initPosition(){
    this->x = 0 + image[state]->w/2;
    this->y =450;
    if(canBeWater){
    this->state = ( rand() %2 );
    }
}

void Floor::render(){

 SDL_Rect offset;


    if(x< -image[state]->w/2 ){
        x=1000 + image[state]->w/2;

        if(this->nextFloor != 0 ){
            nextFloor->x + image[state]->w/2;
        }

        if(canBeWater){
        this->state = ( rand() %2 );
        }
    }

    offset.x = x - image[state]->w/2;
    offset.y = 450 - 12;

SDL_BlitSurface( image[state], NULL, screen, &offset );

/*
    offset.x = x+image->w;
    offset.y = 450 - 12;

    SDL_BlitSurface( image, NULL, screen, &offset );
*/

}
void Floor::goNextTo(Floor *suelo){
//TODO!
}
void Floor::setNextFloor(Floor *nextFloor){
    this->nextFloor =  nextFloor;
}
Floor::~Floor()
{

   SDL_FreeSurface( image[0] );
   SDL_FreeSurface( image[1] );
}
