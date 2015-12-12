#include "Timer.hpp"
#include <SDL2/SDL.h>


Timer::Timer(){
    start_time = 0;
}

Timer::~Timer(){
    
}

void Timer::start(){
    start_time = SDL_GetTicks();
}


uint32_t Timer::getTicks(){
    uint32_t diff = SDL_GetTicks() - start_time;
    return diff;
    
}