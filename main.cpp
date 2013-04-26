/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include <string>
#include "Floor.h"
//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
Timer* update;

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //Set the window caption
    SDL_WM_SetCaption( "SDL Runner Lab Progra 3", NULL );

    //If everything initialized fine
    return true;
}

void frameCap()
{
    int frames_per_seccond = 60;
    if(update->get_ticks() < 1000 / frames_per_seccond)
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / frames_per_seccond ) - update->get_ticks() );
    }
    update->start();
}

int main( int argc, char* args[] )
{
    //Initialize
    init();
    update=new Timer();
    update->start();
    SDL_Surface *game_over = IMG_Load( "game_over.png" );

    Background background(screen);
    Player player(screen);
    Enemy enemy(screen);
    Enemy enemy2(screen);

    Floor floor1(screen,0);
      Floor floor2(screen,1);
      floor2.x = floor1.x + 200;
       Floor floor3(screen,0);
       floor3.x = floor1.x + 400;
        Floor floor4(screen,1);
        floor4.x = floor1.x + 600;
         Floor floor5(screen,0);
         floor5.x = floor1.x + 800;
           Floor floor6(screen,1);
           floor6.x = floor1.x + 1000;

    enemy2.x = enemy.x + 350;
    enemy2.y = enemy.y - 150;

    SDL_Event event;
    //Quit flag
    bool quit = false;

    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_UP: player.jump(); break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        background.logic();
        player.logic();
        enemy.logic();
        enemy2.logic();

        floor1.logic();
        floor2.logic();
        floor3.logic();
        floor4.logic();
        floor5.logic();
        floor6.logic();



        if(player.x-floor1.x<150
           && player.x-floor1.x>-50
           && player.y-floor1.y<128
           && player.y-floor1.y>-150
           && floor1.state == 1
           )
        {

           player.setFloor(900);
        }

      if(player.x-floor2.x<150
           && player.x-floor2.x>-50
           && player.y-floor2.y<128
           && player.y-floor2.y>-150
           && floor2.state == 1
           )
        {

           player.setFloor(900);
        }

        if(player.x-floor3.x<150
           && player.x-floor3.x>-50
           && player.y-floor3.y<128
           && player.y-floor3.y>-150
           && floor3.state == 1
           )
        {

           player.setFloor(900);
        }

      if(player.x-floor4.x<150
           && player.x-floor4.x>-50
           && player.y-floor4.y<128
           && player.y-floor4.y>-150
           && floor4.state == 1
           )
        {

           player.setFloor(900);
        }

      if(player.x-floor5.x<150
           && player.x-floor5.x>-50
           && player.y-floor5.y<128
           && player.y-floor5.y>-150
           && floor5.state == 1
           )
        {

           player.setFloor(900);
        }


      if(player.x-floor6.x<150
           && player.x-floor6.x>-50
           && player.y-floor6.y<128
           && player.y-floor6.y>-150
           && floor6.state == 1
           )
        {

           player.setFloor(900);
        }

        if (player.y > 700){
            break;
        }



        if(player.x-enemy.x<50
           && player.x-enemy.x>-50
           && player.y-enemy.y<50
           && player.y-enemy.y>-50
           )
        {

           break;
        }

        if(player.x-enemy2.x<50
           && player.x-enemy2.x>-50
           && player.y-enemy2.y<50
           && player.y-enemy2.y>-50
           )
        {


           break;
        }


        background.render();
        player.render();
        enemy.render();
        enemy2.render();
        floor1.render();
        floor2.render();
        floor3.render();
        floor4.render();
        floor5.render();
        floor6.render();
        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

    }
    for (int i = 0; i < 5; i++){

        player.die(i);

        background.render();
        player.render();
        enemy.render();
        enemy2.render();
        floor1.render();
        floor2.render();
        floor3.render();
        floor4.render();
        floor5.render();
        floor6.render();

        frameCap();

        SDL_Delay(60);

        /*SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;


        SDL_BlitSurface( game_over, NULL, screen, &offset );
*/
       // frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

floor1.render();
    }
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
        if(player.x-enemy.x<50
           && player.x-enemy.x>-50
           && player.y-enemy.y<50
           && player.y-enemy.y>-50
           )
        {
           break;
        }
         if(player.x-enemy2.x<50
           && player.x-enemy2.x>-50
           && player.y-enemy2.y<50
           && player.y-enemy2.y>-50
           )
        {
           break;
        }

                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;


        SDL_BlitSurface( game_over, NULL, screen, &offset );

        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }



    //SDL_Quit();

    return 0;
}
