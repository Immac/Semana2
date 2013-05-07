#include "Player.h"


Player::Player(SDL_Surface *screen)
{
    this->screen = screen;
    this->loadImages();

    //=== Posicion inicial ==//
    this->initPosition();


 //    Mix_Chunk *jumpSfx = Mix_LoadWAV( "Collision8-Bit.ogg" );

}

void Player::initPosition(){

    this->floor = 450;
    this->state = AIR;
    this->x = 200; if (this->y < 450 + 128){
    this->state = AIR;
   }
    this->y = 0;
    this->acceleration = 6;
    this->velocity = 0;

    //=== Animacion ===//
    this->current_frame = 0;
    this->frame_time_elapsed = 0;
    this->frame_length = 3;


}
int score=0;
void Player::logic()
{   this->playJump = false;
    y+=velocity;
    velocity+=acceleration;


   // int hola = SDLK_UP;



    if(y>=this->floor-images[current_frame]->w/2)
    {
        y=this->floor-images[current_frame]->w/2;
        this ->acceleration=6;
        velocity=0;

    }

    switch (input){
        case SDLK_z:
        case SDLK_UP:
            this->jump();
            this->acceleration = 2;
        break;
        case SDLK_RIGHT:
        case SDLK_x:
            this->jump();
            this->acceleration = 4;
        break;
        case SDLK_DOWN:
        case SDLK_c:
            this->acceleration = 10;
    }


    this->clearInput();
}
void Player::setInput(int input){
    this->input = input;

}
void Player::clearInput(){
this->input = -1;
}
void Player::jump()
{
  if(y>=this->floor-images[current_frame]->w/2)
    {
       velocity=-30;
       this->playJump =  true;
     //  Mix_PlayChannel(-1, jumpSfx, 1);
    }

}

void Player::render()
{
    SDL_Rect offset;

    offset.x = x - images[current_frame]->w/2 - (images[0]->w - images[current_frame]->w)/2;
    offset.y = y - images[current_frame]->h/2 + (images[0]->h - images[current_frame]->h)/1;

    if(y>=this->floor-images[current_frame]->w/2 || current_frame > 4 )
    {
        SDL_BlitSurface( images[current_frame], NULL, screen, &offset );
    } else {
        SDL_BlitSurface( images[4], NULL, screen, &offset );
    }



    if( frame_time_elapsed >= frame_length){
        frame_time_elapsed = 0;
        current_frame++;
        if(current_frame>3){
            current_frame=0;
        }
        }
    frame_time_elapsed++;

}

void Player::die(int i){
    velocity=0;
    current_frame = i + 5;
  }

void Player::setFloor(int i){
this->floor = i;
}

void Player::loadImages(){

    this->images[0] = IMG_Load( "player/1.png" );
    this->images[1] = IMG_Load( "player/2.png" );
    this->images[2] = IMG_Load( "player/3.png" );
    this->images[3] = IMG_Load( "player/4.png" );
    // Jump
    this->images[4] = IMG_Load( "player/5.png" );
    // Die
    this->images[5] = IMG_Load( "player/perder01.png" );
    this->images[6] = IMG_Load( "player/perder02.png" );
    this->images[7] = IMG_Load( "player/perder03.png" );
    this->images[8] = IMG_Load( "player/perder04.png" );
    this->images[9] = IMG_Load( "player/perder05.png" );
}

void Player::kill(){
this->state = DEAD;
}

void Player::checkFloor(Floor *floor){

 if (this->y > 450){
    this->state = FELL;
   }

if(abs(floor->x - this->x) > 199){
   return;
}
    int agua = 100;
    int tierra = 110;
   if(floor->state == 1
      && this->x - floor->x < agua
      && this->x - floor->x > -agua
      ){
        this->setFloor(900);

      }else if (this->state != FELL

      && this->x - floor->x < tierra
      && this->x - floor->x > -tierra
                 ){
        this->setFloor(450);
      }
}



void Player::checkCollision(Enemy *enemy){

    if(this->x-enemy->x<50
        && this->x-enemy->x>-50
        && this->y-enemy->y<50
        && this->y-enemy->y>-50){
           this->kill();
        }
}

bool Player::isDead(){
    if (this->y>650){
        this->kill();
    }
    if(state == DEAD){
        return true;
    }
        return false;
}

Player::~Player()
{
    //== Eliminar las imagenes en el arreglo  de Images ==//
    for(int i = 0 ; i < 10 ; i++ ){
    SDL_FreeSurface( images[i] );
    }
}

