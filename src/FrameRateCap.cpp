#include "FrameRateCap.hpp" 
#include "Timer.hpp"

#include <SDL2/SDL.h>

FrameRateCap::FrameRateCap(){
    cap_timer = new Timer;
    
    setMaxFPS();
}

FrameRateCap::~FrameRateCap(){
    delete cap_timer;
}

void FrameRateCap::setMaxFPS( uint32_t max_fps ){
    max_frames_per_second = max_fps;
    ticks_per_frame = 1000 / max_fps;
}

void FrameRateCap::startTimer( void ){
    cap_timer->start();
}

void FrameRateCap::handleRateCap( void ){
    uint32_t cticks = cap_timer->getTicks();
    if( cticks < ticks_per_frame ){            
        SDL_Delay( ticks_per_frame - cticks );
    }   
}