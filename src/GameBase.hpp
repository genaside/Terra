#ifndef GAMEBASE_HPP 
#define GAMEBASE_HPP

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstddef>


/**
 * 
 */
class GameBase{
    public:
        //GameBase( void );        
        //~GameBase( void );
        
        
        SDL_Texture* loadTexture( SDL_Renderer* renderer, std::string image_path ){
            //The final texture
            SDL_Texture* newTexture;

            //Load image at specified path
            SDL_Surface* loadedSurface = IMG_Load( image_path.c_str() );
            if( !loadedSurface ){
                printf( "Unable to load image %s! SDL_image Error: %s\n", image_path.c_str(), IMG_GetError() );
                exit( EXIT_FAILURE );
            }else{
                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                if( !newTexture ){
                    printf( "Unable to create texture from %s! SDL Error: %s\n", image_path.c_str(), SDL_GetError() );
                }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
            }

            return newTexture;
        }
        
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
       
};





#endif // GAMEBASE_HPP
