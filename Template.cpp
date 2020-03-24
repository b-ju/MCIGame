//
//  Template.cpp
//  Question_Template
//
//  Created by ben jurenka on 3/19/20.
//  Copyright © 2020 ben jurenka. All rights reserved.
//

#include "Template.h"

//constructor
Template::Template(){
    if( Init() != 0 ){
        printf("Could not initialize variables of TheGame");
    }
}
// ************** Init ************************
// Initializes:  SDL, window, renderer, TTF_INIT, IMG_INIT
int Template::Init(){
            
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
         return -1;
    }
            //Set texture filtering to linear
     if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
         printf( "Linear texture filtering not enabled!" );
     }
            
     window = SDL_CreateWindow("Test Question", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_LENGTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
     
     if (window == NULL || renderer == NULL) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
         return -1;
     }
     
     //Initialize renderer color
     SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

         //Initialize jpG loading
     int jpgFlags = IMG_INIT_JPG;
     if( !( IMG_Init( jpgFlags ) & jpgFlags ) ) {
             printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
             return -1;
         }
          //Initialize SDL_ttf
     if( TTF_Init() == -1 ) {
             printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
             return  -1;
         }

    return 0;
}

// ************* OnEvent ******************
// key board events will be read into here

void Template::OnEvent(SDL_Event *Event){
    if(Event->type == SDL_QUIT) {
        Cleanup();
    }
     //User presses a key
    else if( Event->type == SDL_KEYDOWN ) {
        switch( Event->key.keysym.sym ) {
                    case SDLK_UP:
                        printf("Up key pressed.\n");
                        if(answer > 0){
                            up = true;
                            answer--;
                        }
                    break;

                    case SDLK_DOWN:
                        printf("Down key pressed.\n");
                        if(answer < 3){
                            down = true;
                            answer++;
                        }
                    break;

                    case SDLK_SPACE:
                        printf("Space key pressed.\n");
                        if( nextQ == false && ( skip == false || checkAnswer == false )){
                            nextQ = true;
                        }
                    break;
                    
                    case SDLK_RETURN:
                        printf("Return key pressed.\n");
                        if(checkAnswer == false && skip == false){
                            checkAnswer = true;
                        }
                        
                    break;
                               
                    case SDLK_ESCAPE:
                        printf("Esc key pressed.\n");
                        if(checkAnswer == false && skip == false){
                         skip = true;
                        }
                    break;
                               
                    default:
                    break;
        }
    }
}

//************** Cleanup *************
//Destoy all objects and quit all API'S

void Template::Cleanup(){
        printf("Clean up.\n");
      
                //Free font
        TTF_CloseFont( font );
        font = NULL;
        
                //destoy everything that was created
        SDL_DestroyTexture(background_tex);
        SDL_DestroyTexture(text_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;
        delete[] highlight_answers;
    
                //quit all APIs
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
}

// *************** main ************8
// creates Game object,
// initialis 2 string arrays with question ans answers,
// calls AskQuestion with both arrays as inputs
int main(int argc, char* argv[]) {
    //creat a game object
    Template game = Template();
    
    std::array<std::string, 5> qAndA =  {"What is the answer to life the universe and everything?",
         "beer",
        "cookies",
        "42",
        "simulation theory"};
    std::array<std::string, 5> qAndA_2 =  {"What is the name of Larry David's coffee shop?",
           "Latte Larrys",
          "Mocha Joes",
          "Guava Garrys",
          "Cosmic Coffee"};
    
            //2 means the 3rd box down will be correct answer
    game.AskQuestion(qAndA, 2 );
            
            //0 means 1st box down will be correct answer
    game.AskQuestion(qAndA_2, 0);
            
    game.Cleanup();
    return 0;
}
