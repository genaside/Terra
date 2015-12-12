#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP


enum class GameStates{ NONE, TITLE, MAIN_GAME, EXIT };

class GameState{
    public:
        virtual void handleEvents() = 0;
        virtual void logic() = 0;
        virtual void draw() = 0;
        
        virtual ~GameState(){};

        GameStates* next_game_state;    
};


#endif // GAMESTATE_HPP

