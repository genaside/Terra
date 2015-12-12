#ifndef TIMER_HPP
#define TIMER_HPP


#include <cstdint>

class Timer{
    public:
        Timer( void );
        ~Timer( void );
        
        void start( void );
        
        
        uint32_t getTicks( void );
        
    private:
        uint32_t start_time;
};







#endif // TIMER_HPP
