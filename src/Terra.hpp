#ifndef TERRA_HPP
#define TERRA_HPP

#include "GameBase.hpp"
#include "GameState.hpp"

class Terra{
    public:
        Terra( void );
        ~Terra( void );
    
        void start( void );
        
    private:
        void InitSDL( void );
        void createWindow( void );
        void mainLoop( void );
        
        void changeGameState( void );
        
        
        GameStates current_state_id;
        GameStates next_state_id;
        
        GameState* game_state_ptr; //
    
        SDL_Window* window;
        SDL_Renderer* renderer;
    
};







#endif // TERRA_HPP
