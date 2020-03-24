//
//  TheGame.hpp
//  Question_Template
//
//  Created by ben jurenka on 3/19/20.
//  Copyright © 2020 ben jurenka. All rights reserved.
//

#ifndef Template_h
#define Template_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <array>

class Template {
public:
    Template( );         //creates a game object that calls Init()

    int Init( );        // function that initializes everything - SDL_Init(...), window, renderer, TTF_INIT, IMG_INIT
    
    void OnEvent(SDL_Event *Event);         //any key board event will be read into here
            
    void Cleanup( );        //Destoy all objects and quit all API'S
    
    int InitQuestion( );    //load background pic for question, and create rectangles for answer boxes
   
    void AskQuestion(  std::array<std::string, 5> qAndA, int answer );

    void OnQuestion( );     //controler for question
    
    void DisplayQuestion( );        //renders images and images for question to window
    
    void RenderText(std::string sentence, int font_size, int x, int y, SDL_Rect* clip,          //renders texts
                    double angle, SDL_Point* center, SDL_RendererFlip flip );
    void ResetQuestion( );          //reset variables used in OnQuestion


private:
        const int WINDOW_HEIGHT = 300;
        const int WINDOW_LENGTH = 500;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event Event;
            
            //variables for renderering background image
        SDL_Texture *background_tex;
        SDL_Surface *surface;
        int imageWidth;
        int imageHeight;
      
            //variables for text renderer
        TTF_Font *font;
        SDL_Texture *text_texture;
        SDL_Surface *text_surface;
        int text_Width;
        int text_Height;
      
    
            //variables for question function
        SDL_Rect src_rect;
        SDL_Rect dest_rect;
        SDL_Point center;                               //used for RenderText
        std::array<std::string, 5> qAndA;
        SDL_Rect* highlight_answers = new SDL_Rect[4];
        SDL_RendererFlip flip = SDL_FLIP_NONE;          //used for RenderText
     
        bool nextQ = false;
        bool skip = false;          //when user presses esc button during questing: skip question
        bool checkAnswer = false;   //when user presses enter: check answer
        bool up = false;            //when user presses up: move highlighted answer up and number of answer up
        bool down = false;          //when user presses down: move highlighted answer down and number of answer down
        int answer = 0;         //number of answer user has selected
        int correct = 0;        //number of the correct answer: can be set to 0-3
};

#endif /* Template_h */
