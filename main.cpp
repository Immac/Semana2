/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
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
const int FRAMECAP = 60;
const int GAMEOVERCAP = 10;
SDL_Surface *screen = NULL;
Timer* update;


std::string toString(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}


bool init()
{
 //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
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

void frameCap(int i)
{
    int frames_per_seccond = i;
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
     SDL_Surface *splash = IMG_Load( "splash.png" );
    int score=0;
    int deaths = 0 ;
    Background background(screen);

    TTF_Font *font = TTF_OpenFont( "pokeh.ttf", 128 );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface * score_surface = NULL;
     SDL_Surface * muertes_surface = NULL;
    Mix_Chunk *jump = Mix_LoadWAV( "Collision8-Bit.ogg" );
    Mix_Chunk *die = Mix_LoadWAV( "death.ogg" );
    Mix_Music *music = NULL;


    Player player(screen);
    Enemy enemy(screen);

    Floor floor1(screen,1);

    Floor floor2(screen,0);
    Floor floor3(screen,0);
    Floor floor4(screen,0);
    Floor floor5(screen,1);
    Floor floor6(screen,0);
    floor1.setNextFloor(&floor6);
    floor2.setNextFloor(&floor5);
    floor3.setNextFloor(&floor4);
    floor4.setNextFloor(&floor3);
    floor5.setNextFloor(&floor2);
    floor6.setNextFloor(&floor1);



    SDL_Event event;
    //Quit flag
    bool quit = false;

    while (quit == false){
            Mix_HaltMusic();
        Mix_FreeMusic(music);
    music = NULL;
      if(music == NULL) {

	/* Actually loads up the music */
	music = Mix_LoadMUS("intro.ogg");
      }

Mix_PlayMusic(music, -1);



while( quit == false ){



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
                }

                break;

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


        SDL_BlitSurface( splash, NULL, screen, &offset );

        frameCap(FRAMECAP);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

        Mix_HaltMusic();
        Mix_FreeMusic(music);
    music = NULL;
      if(music == NULL) {

	/* Actually loads up the music */
	music = Mix_LoadMUS("music.ogg");
      }


    score = 0 ;
    player.initPosition();
    floor1.initPosition();
    floor2.initPosition();
    floor2.x = floor1.x + 200;
    floor3.initPosition();
    floor3.x = floor1.x + 400;
    floor4.initPosition();
    floor4.x = floor1.x + 600;
    floor5.initPosition();
    floor5.x = floor1.x + 800;
    floor6.initPosition();
    floor6.x = floor1.x + 1000;

    enemy.initPosition();

   //  enemy.y = enemy.y - 200;
Mix_PlayMusic(music, -1);


   while( quit == false ){
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {   //=== Set input for player ===//
            player.setInput(event.key.keysym.sym);

                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;

                    break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

    //=== BG logic ===//
        background.logic();
      //=== Hazard Logic ===//
        enemy.logic();


        floor1.logic();
        floor2.logic();
        floor3.logic();
        floor4.logic();
        floor5.logic();
        floor6.logic();  // Because floor logic!

    //=== Player Logic ===//

        player.checkFloor(&floor1);
        player.checkFloor(&floor2);
        player.checkFloor(&floor3);
        player.checkFloor(&floor4);
        player.checkFloor(&floor5);
        player.checkFloor(&floor6);

        player.checkCollision(&enemy);

        if (player.isDead()){
            break;
        }


        player.logic();
        if (player.playJump){ // Play sound
            Mix_PlayChannel( -1, jump, 0 );
        }





    //=== Render ALL THE THINGS ===//
        background.render();
        player.render();
        enemy.render();

        floor1.render();
        floor2.render();
        floor3.render();
        floor4.render();
        floor5.render();
        floor6.render();

    //=== Score System ===/

        SDL_Rect offset;

        offset.x = 0;
        offset.y = 0;

        SDL_Surface * score_surface = TTF_RenderText_Solid( font,
            toString(score+=5).c_str(),
            textColor ); //char apuntador :)   // NOOOOOOOOOOOAHHHH!!!!!1!11!!

        SDL_BlitSurface( score_surface, NULL, screen, &offset );

        SDL_FreeSurface( score_surface );



        frameCap(FRAMECAP);

        //Update the screen
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }

    }

Mix_PlayChannel( -1, die, 0 );
    for (int i = 0; i < 5; i++){

        player.die(i);

        background.render();
        player.render();
        enemy.render();

        floor6.render();
        floor5.render();
        floor4.render();
        floor3.render();
        floor2.render();
        floor1.render();
        Mix_HaltMusic();
        Mix_FreeMusic(music);

        frameCap(GAMEOVERCAP);
        //=== Update the screen ===//
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }


    }
    music = NULL;
                 if(music == NULL) {

	/* Actually loads up the music */
	music = Mix_LoadMUS("sad.ogg");
      }

    Mix_PlayMusic(music,-1);
        frameCap(GAMEOVERCAP);

    deaths++;
    while( quit == false ){


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
                }

                break;

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


        SDL_Surface * muertes_surface = TTF_RenderText_Solid( font,
            ("Muertes:" + toString(deaths)).c_str(),
            textColor ); //char apuntador :)   // NOOOOOOOOOOOAHHHH!!!!!1!11!!

        SDL_BlitSurface( game_over, NULL, screen, &offset );
        SDL_BlitSurface( muertes_surface, NULL, screen, &offset );

        SDL_FreeSurface( muertes_surface );



        frameCap(FRAMECAP);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    }

    //SDL_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return 0;
}

