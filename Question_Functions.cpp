//
//  DisplayQuestion.cpp
//  Question_Template
//
// Extension of Template.cpp

#include <stdio.h>
#include "Template.h"


// *********** InitQuestion ************
// Loads background pic for question, and create rectangles for answer boxes

int Template::InitQuestion(){
        //make sure texture is free to use
    if(background_tex != NULL){
        background_tex = NULL;
    }
            //load background image for question
    surface = IMG_Load("pic.jpg");
    
    if(surface == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't load image: %s", SDL_GetError());
        return -1;
    }
    
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF));
     
            //create texture from loaded image
    background_tex = SDL_CreateTextureFromSurface(renderer, surface);
   
    if(text_texture == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't create texture: %s", SDL_GetError());
    }
    
    SDL_FreeSurface(surface);
    
               //fill locations for answer box highlights
    SDL_Rect temp_rect;
    
    temp_rect.w = 22;
    temp_rect.h = 22;
    temp_rect.x = 34;
    temp_rect.y = 54;
    
                //all rects have same values except for the y value
    for(int i = 0; i < 4; i++){
        temp_rect.y += 43;
        highlight_answers[i] = temp_rect;
    }

    return 0;
}

//************ AskQuestion ****************
//Control function for asking a questing.
//Sets the 5 strings needed for question and the index of the correct answer (0-3)
//Calls InitQuestion, OnQuestion, ResetQuestion
//Parameters :
                //qAndA: array of  5 strings, with qAndA[0] being the question, the rest are answer choices
                //answer: index of correct answer(0-3).

void Template::AskQuestion(  std::array<std::string, 5> qAndA, int answer ) {
    this->qAndA = qAndA;
    this->correct = answer;
    printf("initialize question...\n");
     if( InitQuestion() != 0){
         printf("could not initialize question");
     }
    printf("asking question...\n");
    OnQuestion();
    printf("reseting question...\n");
    ResetQuestion();
}

//**************** OnQuestion ***************
//displays question, and if user was right or wrong, waits on user input from keys: up, down, enter, esc, space
//Up/ Down keys : Changes the "highlight" og rectangle next to each answer
//Enter: submits answer
//esc: skips the question
//space: goes to next question after answer or skip has been pressed.

void Template::OnQuestion( ) {
   printf("In question function.\n");

    center.x = 100;
    center.y = 35;
    
    //set background
    DisplayQuestion( );
    SDL_RenderPresent(renderer);
    
    while( skip == false && checkAnswer == false ) {
        while( SDL_PollEvent(&Event) ) {
            //pass event to OnQEvent to handle
            OnEvent(&Event );
            //once there are no more events in queue,SDL Poll_Event
            //retuns false, exit Event queue loop
        }
            if( up ){
                DisplayQuestion( );
                up = false;

            } else if( down ){
                DisplayQuestion( );
                down = false;
            } else if( skip ){
                skip = true;
            }
        SDL_RenderPresent(renderer);
    }
    
    SDL_RenderClear(renderer);

        if (skip == true) {
             printf("Skipped question.\n");
             RenderText("skipped", 32, 100, 100, NULL, 0, &center, flip);
        } else if (answer == correct) {
            printf("Answer correct!\n");
            RenderText("CORRECT!",32, 100, 100, NULL, 0, &center, flip);
        } else {
            printf("Wrong!\n");
            RenderText("WRONG!",32, 100, 100, NULL, 0, &center, flip);
        }
    
    RenderText("press space to continue...", 18, 250, 269, NULL, 0, &center, flip);
    SDL_RenderPresent(renderer);
    while( nextQ == false ){
        while( SDL_PollEvent(&Event) ) {
            OnEvent(&Event);
        }
    }
    printf("End of questioning.\n");
}


//******** DisplayQuestion *********
// renderers everything for question : background texture, answer boxes, answerbox highlights.
// Calls RenderText for question ans answer strings.
void Template::DisplayQuestion ( ) {
    
    SDL_RenderCopy(renderer, background_tex, NULL, NULL);
            //rectangle for question
    src_rect.w = 440;   //width
    src_rect.h = 50;    //height
    src_rect.x = 30;    //x location of upper left corner
    src_rect.y = 30;    //y locationa of upper leftt corner

            //color of rectangle
    SDL_SetRenderDrawColor(renderer, 255, 51, 153, 255);
    SDL_RenderFillRect(renderer, &src_rect);            //put rectangle into renderer
    SDL_RenderCopy(renderer, NULL, &src_rect, NULL);    //put rect over background
    
                //rectangle for answer boxes
    src_rect.w = 30;    //width
    src_rect.h = 30;    //height
    src_rect.y = 50;    //y locationa of upper leftt corner
    
            //color for answer boxes
    SDL_SetRenderDrawColor(renderer, 255, 55, 255, 255);
    
    //create 4 boxes and render
    for(int i = 0; i < 4; i++) {
        src_rect.y += 43;                                       //y locationa of upper left corner
        SDL_RenderFillRect(renderer, &src_rect);                //put rectangle into renderer
        SDL_RenderCopy(renderer, NULL, &src_rect, NULL);         //put rect over background
    }
    
    SDL_SetRenderDrawColor(renderer, 153, 51, 255, 255);
    SDL_RenderFillRect(renderer, &highlight_answers[answer]);  //put rectangle into renderer
    SDL_RenderCopy(renderer, NULL, &highlight_answers[answer], NULL); //put rect over background
    
    SDL_Point center;
    
    center.x = 100;
    center.y = 35;
    
    //render question and answers
    RenderText(qAndA[0],18, 35, 35, NULL, 0, NULL, flip);
    
    int y = 46;
    for(int i = 1; i < 5; i++){
        RenderText(qAndA[i].c_str(),26, 65, y += 47, NULL, 0, NULL, flip);
    }
}


//************ RenderText *******************
// renders text to window
//  Variables ->
//      sentence : the string to render to screen,
//      font_size : int for size of font
//      x,y : ints for location on window to render to.
//      clip:
//      angle: double of rotation in degrees around center
//      center: used for setting angle
//      flip :
//
void Template::RenderText(std::string sentence, int font_size, int x, int y, SDL_Rect* clip,
                         double angle, SDL_Point* center, SDL_RendererFlip flip ){
                //set font to the font that will be used, and size of text
        font = TTF_OpenFont( "SF_Archery_Black.ttf", font_size );
        
                //make sure font loaded successfully
        if( font == NULL ){
             printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
         }
                //set text color
         SDL_Color textColor = {
             55, 55, 255
         };
                //set surface from: font, a c style string, and text color
        text_surface = TTF_RenderText_Solid( font, sentence.c_str(), textColor );

                //make sure surface loaded successfully
         if( text_surface == NULL ){
             printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
         }
                //Create texture from surface pixels
         text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
            
                //make sure texture loaded successfully
         if( text_texture == NULL ){
                 printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
         } else {
                 //if text_texture loaded successfully: Get image dimensions
                     text_Width = text_surface->w;
                     text_Height = text_surface->h;
         }
                //done with this surface, so free it
        SDL_FreeSurface( text_surface );
                //initialize a rect for SDL_RenderCopyEx
        SDL_Rect renderQuad = {
            x, y, text_Width, text_Height
        };
                //Set clip rendering dimensions
        if( clip != NULL ) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
                    //Render to screen
        SDL_RenderCopyEx( renderer, text_texture, clip, &renderQuad, angle, center, flip );
    }

//******* ResetQuestion ************
// resets variables used in OnQuestion( )
void Template::ResetQuestion(){
    answer = 0;
    nextQ = false;
    skip = false;
    checkAnswer = false;
}

