#include "TitleScreen.hpp" 

TitleScreen::TitleScreen( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs ){
    this->window = window;
    this->renderer = renderer;
    this->next_game_state = gs;
    
    // Load stuff
    splash = loadTexture( renderer, "./assets/images/splash.png" );
} 

TitleScreen::~TitleScreen(){
    SDL_DestroyTexture( splash );
}



void TitleScreen::logic(){
    
}

void TitleScreen::handleEvents(){
    SDL_Event event;
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_QUIT:
                printf( "Window close, exting game.\n" );
                *next_game_state = GameStates::EXIT;                
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){                    
                    *next_game_state = GameStates::EXIT;
                }else if( event.key.keysym.sym == SDLK_SPACE ){
                    *next_game_state = GameStates::MAIN_GAME;                            
                }
        }
    }      
}

void TitleScreen::draw(){
    SDL_RenderClear( renderer );
    SDL_RenderCopy( renderer, splash, NULL, NULL );
        
    SDL_RenderPresent( renderer );
}