#ifndef MAINGAME_HPP
#define MAINGAME_HPP

#include "GameState.hpp"
#include "GameBase.hpp"

class MainGame : public GameState , private GameBase{
    public:
        MainGame( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs );
        ~MainGame( void );
        
        void logic( void );
        void handleEvents( void );
        void draw( void );        
    private:
        enum movement{ LEFT = 1, RIGHT, UP, DOWN, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT  }; 
        enum action{ JUMP = 1, FIRE  };
};




#endif // MAINGAME_HPP
