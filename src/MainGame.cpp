#include "MainGame.hpp"

MainGame::MainGame( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs ){    
    this->window = window;
    this->renderer = renderer;
    this->next_game_state = gs;
   
}

MainGame::~MainGame(){
     
}

void MainGame::logic(){
        
    
    
}

void MainGame::handleEvents(){
    SDL_Event event;
    
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_QUIT:                
                *next_game_state = GameStates::EXIT;                
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){                    
                    *next_game_state = GameStates::TITLE;
                }               
                break;            
        }
    } 
    /*
    // Handle movements    
    const Uint8* ks = SDL_GetKeyboardState( NULL );
    
    // first do cancelations then diagonals, then sigles
    
    if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_DOWN ]  ){
        // nothing 
    }else if( ks[ SDL_SCANCODE_LEFT ] && ks[ SDL_SCANCODE_RIGHT ] ){
        //nothing
    }else if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_LEFT ] ){
        ship.movement = movement::UP_LEFT;
    }else if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_RIGHT ] ){
        ship.movement = movement::UP_RIGHT;
    }else if( ks[ SDL_SCANCODE_DOWN ] && ks[ SDL_SCANCODE_RIGHT ] ){
        ship.movement = movement::DOWN_RIGHT;
    }else if( ks[ SDL_SCANCODE_DOWN ] && ks[ SDL_SCANCODE_LEFT ] ){
        ship.movement = movement::DOWN_LEFT;
    }else if( ks[ SDL_SCANCODE_UP ] ){
        ship.movement = movement::UP;        
    }else if( ks[ SDL_SCANCODE_DOWN ] ){ 
        ship.movement = movement::DOWN;           
    }else if( ks[ SDL_SCANCODE_LEFT ] ){ 
        ship.movement = movement::LEFT;        
    }else if( ks[ SDL_SCANCODE_RIGHT ] ){
        ship.movement = movement::RIGHT;
    }
    
    // fire buttons
    if( ks[ SDL_SCANCODE_SPACE ] ){
        //std::cout << "Status: primary fire." << std::endl;
        primary_fired = true;
    }
    */
}




void MainGame::draw(){
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF ); 
    SDL_RenderClear( renderer );
    SDL_RenderPresent( renderer );
}


