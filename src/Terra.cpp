#include "Terra.hpp"
#include "TitleScreen.hpp" 
#include "MainGame.hpp"
#include "FrameRateCap.hpp" 



Terra::Terra(){   
    // Nothing
}


Terra::~Terra(){
    // Close all sdl components
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();    
}


void Terra::start(){
    InitSDL();
    createWindow();
    
    mainLoop();
    
}

void Terra::InitSDL(){
    int status;
    
    // Main SDL
    //status = SDL_Init( SDL_INIT_VIDEO  );
    status = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS );
    
    if( status < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }    
    
    // Init image features
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    status = IMG_Init( img_flags );
    if( !( status & img_flags ) ){
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        exit( EXIT_FAILURE );
    }    
    
    // Init music/sound features
    status = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    if( status < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        exit( EXIT_FAILURE );
    }
    
    // Init Fonts
    status = TTF_Init();
    if( status < 0 ){
        printf( "SDL_tff could not initialize! SDL_tff Error: %s\n", TTF_GetError() );
        exit( EXIT_FAILURE );
    }
    
}

void Terra::createWindow(){
    window = SDL_CreateWindow(
        "Terra",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        480,
        SDL_WINDOW_SHOWN        
    );

    if( !window ){
        printf("Unable create window: %s\n", SDL_GetError());
        exit( EXIT_FAILURE );
    }

    // Now the renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/ );
    if( !renderer ){
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        exit( EXIT_FAILURE );
    }
}


void Terra::mainLoop(){
    
    FrameRateCap frc;
    frc.setMaxFPS( 60 );
    
    next_state_id = GameStates::NONE;
    current_state_id = GameStates::TITLE;    
    game_state_ptr = new TitleScreen( window, renderer, &next_state_id );
    
        
    while( current_state_id != GameStates::EXIT ){  
        frc.startTimer();
        
        game_state_ptr->logic();
        game_state_ptr->handleEvents(); 
        game_state_ptr->draw();
        
        frc.handleRateCap();        
        
        changeGameState();        
    }
}

void Terra::changeGameState(){
    if( next_state_id != GameStates::NONE ){
        if( next_state_id != GameStates::EXIT ){
            delete game_state_ptr;
        }
        
        
        switch( next_state_id ){            
            case GameStates::TITLE:
                game_state_ptr = new TitleScreen( window, renderer, &next_state_id );
                break;     
            case GameStates::MAIN_GAME:
                game_state_ptr = new MainGame( window, renderer, &next_state_id );
                break; 
        }
       
        current_state_id = next_state_id;
        next_state_id = GameStates::NONE;
    }    
}




















