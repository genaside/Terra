#ifndef FRAMERATECAP_HPP
#define FRAMERATECAP_HPP

#include <cstdint>


class Timer;

class FrameRateCap{
    public:
        FrameRateCap( void );
        ~FrameRateCap( void );
        
        void setMaxFPS( uint32_t max_fps = 60 );
        inline uint32_t getMaxFPS( void ){ return max_frames_per_second; }
        
        void startTimer( void );
        void handleRateCap( void );
    private:
        uint32_t max_frames_per_second;
        uint32_t ticks_per_frame;
        
        Timer* cap_timer;
};




#endif // FRAMERATECAP_HPP
