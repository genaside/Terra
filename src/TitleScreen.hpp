#ifndef TITLESCREEN_HPP
#define TITLESCREEN_HPP

#include "GameState.hpp"
#include "GameBase.hpp"


class TitleScreen : public GameState , private GameBase{
    public: 
        TitleScreen( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs );
        ~TitleScreen( void );        
        
        void logic( void );
        void handleEvents( void );
        void draw( void );
    private:     
        SDL_Texture* splash;
       
    
};


#endif // TITLESCREEN_HPP
 
