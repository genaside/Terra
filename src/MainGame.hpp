#ifndef MAINGAME_HPP
#define MAINGAME_HPP

#include "GameState.hpp"
#include "GameBase.hpp"
#include "Timer.hpp"

#include <map>
#include <list>

#include <lua.hpp>


class MainGame : public GameState , private GameBase{
    public:
        MainGame( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs );
        ~MainGame( void );
        
        void logic( void );
        void handleEvents( void );
        void draw( void );        
    private:
        void loadWorld( void );
        void loadCharacters( void );
        void initCamera( void );
        
        bool isMovalbeArea( int, int, int, int );
        bool isOutsideWorld( int, int );
        void centerCameraOnPlayer( void );
        void moveCamera( int, int );
        void deleteObjectsOutsideWorld( void );
        
        
        void drawWorld( void );
        void drawObjects( void );
        void drawCharacters( void );
        
        enum class movement_states{ NONE, LEFT, RIGHT, UP, DOWN, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT  }; 
        enum class action{ JUMP = 1, FIRE  };
        enum class sprite_states{ RIGHT, LEFT, JUMP_LEFT, JUMP_RIGHT }; // sprite states
        
        
        struct sprite{
            SDL_Texture* texture;
            SDL_Rect rect;
        };
        
        struct{
            int xpos;
            int ypos;
            int jump_distance;
            int jump_counter;
            Timer time_last_seed_thrown;
            bool seed_thrown;
            bool jump;
            bool is_standing;
            //bool is_airborn;
            movement_states movement_state;
            sprite_states state;
        } player;
        
        struct{
            int width;
            int height;
            int block_size;
        }world;
        
        SDL_Rect camera;             
        
        // Spite sheets
        SDL_Texture* spritesheet_world;
        SDL_Texture* spritesheet_characters;
        
        std::map <std::string, SDL_Rect> sprites;
        //std::map <std::string, std::pair<SDL_Rect, SDL_Rect>> sprites;        
        std::map <std::string, SDL_Texture*> images; // backgrounds and other non sprite stuff
        
        // things to animate
        std::list< std::pair<std::string, SDL_Point>> world_objects;
        
        lua_State *lua;
};




#endif // MAINGAME_HPP
