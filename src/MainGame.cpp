#include "MainGame.hpp"

MainGame::MainGame( SDL_Window* window, SDL_Renderer* renderer, GameStates* gs ){    
    this->window = window;
    this->renderer = renderer;
    this->next_game_state = gs;
    
    // Lua
    lua = lua_open();
    luaL_openlibs( lua );
    
    if( luaL_loadfile( lua, "./src/World.lua" ) != 0 ){
        lua_error( lua );            
    }    
    if( lua_pcall( lua, 0, 0, 0 ) != 0 ){
        lua_error( lua );            
    }    
    // NOTE, right now the "world" table is the first and only thing in the stack
    lua_getglobal( lua, "world" );    
    
    world.block_size = 64;
    world.width = 50 * world.block_size;
    world.height = 50 * world.block_size;
    
    /*
    
    // Get function
    lua_getglobal( lua, "isOutsideWorld" );
    if( lua_pcall( lua, 0, 1, 0 ) != 0 ){
        lua_error( lua );            
    }
    
    
    / retrieve result /
    printf( "message:%s\n",  lua_tostring( lua, -1 ) );
    */
    
    
    // init var
    player.xpos = 100;
    player.ypos = 0;
    player.jump_distance = 160;
    player.jump_counter = 0;
    player.jump = false;
    player.state = sprite_states::RIGHT;
    
    // starting camera
    camera.x = 0;
    camera.y = 0;
    SDL_GetWindowSize( window, &camera.w, &camera.h );
    
    loadWorld();
    loadCharacters();
}

MainGame::~MainGame(){
    lua_close( lua );  
    SDL_DestroyTexture( spritesheet_world ); 
    SDL_DestroyTexture( spritesheet_characters );
}

void MainGame::loadWorld(){
    // Load world spritesheet
    spritesheet_world = loadTexture( renderer, "./assets/images/spritesheet_world.png" );
        
    // Organize individual sprites
    sprites[ "earth" ] = { 64, 0, 64, 64 };    
    sprites[ "plantform" ] = { 0, 129, 64,31 };
    sprites[ "stem" ] = { 89, 128, 13, 63 };
    sprites[ "seed" ] = { 0, 192, 42, 64 };
    
    /*
    // Set positions in the first sheet
    lua_getfield( lua, 1, "block_types" );
    lua_pushnil( lua );
    
    
    while( lua_next( lua, -2 ) != 0 ){   
        std::string key_name;
        SDL_Rect rect;          
        
        // get name of key
        key_name = lua_tostring( lua, -2 );                
                
        int index = lua_gettop( lua );        
        
        lua_getfield( lua, index, "x" );
        lua_getfield( lua, index, "y" );
        lua_getfield( lua, index, "w" );
        lua_getfield( lua, index, "h" );        
        rect.x = ( int )lua_tointeger( lua, -4 );
        rect.y = ( int )lua_tointeger( lua, -3 );
        rect.w = ( int )lua_tointeger( lua, -2 );
        rect.h = ( int )lua_tointeger( lua, -1 );     
        // 
        lua_pop( lua, 4 );
        
        sprites[ key_name ] = rect;
       
        lua_pop( lua, 1 );
    }   
    
    lua_pop( lua, 1 );   
    */
}

void MainGame::loadCharacters(){
    spritesheet_characters = loadTexture( renderer, "./assets/images/spritesheet_characters.png" );
    sprites[ "Terra_test1" ] = { 0, 0, 128, 128 };    
    sprites[ "Terra_test2" ] = { 128, 0, 128, 128 };
}


void MainGame::logic(){        
    //gavity
    if( player.jump_counter == 0 ){
        if( isMovalbeArea( player.xpos, player.ypos + 7, 64, 64 ) ){
            player.ypos += 7;
            player.is_standing = false;
        }else{
            player.is_standing = true;
        }
    }
    
    
    if( player.movement_state == movement_states::LEFT  ){
        player.state = sprite_states::LEFT;
        if( isMovalbeArea( player.xpos - 4, player.ypos, 64, 64 ) ){
            player.xpos -= 4;
        }
        player.movement_state = movement_states::NONE;
    }else if( player.movement_state == movement_states::RIGHT ){
        player.state = sprite_states::RIGHT;
        if( isMovalbeArea( player.xpos + 4, player.ypos, 64, 64 ) ){
            player.xpos += 4;
        }
        player.movement_state = movement_states::NONE;
    }
    
    
    if( player.jump ){
        if( player.is_standing ){
            if( player.jump_counter < player.jump_distance ){
                player.jump_counter += 10;
                player.ypos -= 10;
            }else{
                player.jump = false;
                player.jump_counter = 0;
            }
            
            //player.is_standing = false;
        }else{
            player.is_standing = false;
            player.jump = false;
        }
        
    }
    
    
    if( isOutsideWorld( player.xpos, player.ypos ) ){
        std::cout << "Player died" << std::endl;  
        exit(1); // TODO
    }
    
    //center cam on charater
    //camera.x = player.xpos - camera.w / 2;
    //camera.y = player.ypos - camera.h / 2;
    
    //
    if( player.seed_thrown ){
        int time = player.time_last_seed_thrown.getTicks();        
        if( time > 600 ){
            std::cout << "Player had thown a seed" << std::endl; 
            SDL_Point point = { player.xpos, player.ypos };
            world_objects.push_back( std::make_pair( "seed" , point ) );
            player.time_last_seed_thrown.start();
        }else{
            player.seed_thrown = false;
        }       
    }
    
    // calculate objects
    for( auto& element : world_objects ){
        element.second.y += 4;     
        if( !isMovalbeArea( element.second.x, element.second.y, 32, 32 ) ){
            std::cout << "seed landed" << std::endl; 
            
        }
    }
    
    
    
    deleteObjectsOutsideWorld();
}

bool MainGame::isMovalbeArea( int x, int y, int w, int h ){
    bool check;
    
    lua_getglobal( lua, "isNonPassable" );
    lua_pushinteger( lua, x );
    lua_pushinteger( lua, y );
    lua_pushinteger( lua, w );
    lua_pushinteger( lua, h );    
    if( lua_pcall( lua, 4, 1, 0 ) != 0 ){
        lua_error( lua );            
    }
    
    check = lua_toboolean( lua, -1 );    
    lua_pop( lua, 1 ); 
    
    return !check;
}

bool MainGame::isOutsideWorld( int x, int y ){
    if( x < 0 || x > world.width || y < 0 || y > world.height  ){        
        return true;
    }else{
        return false;
    }
}


void MainGame::centerCameraOnPlayer(){
    
}

void MainGame::moveCamera( int x, int y ){
    
}


void MainGame::deleteObjectsOutsideWorld(){
    for( auto i = world_objects.begin(); i != world_objects.end(); ){        
        if( (*i).second.y > world.height  ){
            i = world_objects.erase( i );
            std::cout << "Seed deleted" << std::endl; 
        }else{
            ++i;
        }
    }
}


void MainGame::handleEvents(){
    SDL_Event event;
    
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_QUIT:                
                *next_game_state = GameStates::EXIT;                
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){                    
                    *next_game_state = GameStates::TITLE;
                }               
                break;            
        }
    } 
    
    
    // Handle movements    
    const Uint8* ks = SDL_GetKeyboardState( NULL );
    
    // first do cancelations then diagonals, then sigles
    
    if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_DOWN ]  ){
        // nothing 
    }else if( ks[ SDL_SCANCODE_LEFT ] && ks[ SDL_SCANCODE_RIGHT ] ){
        //nothing
    }else if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_LEFT ] ){
        //ship.movement = movement::UP_LEFT;
    }else if( ks[ SDL_SCANCODE_UP ] && ks[ SDL_SCANCODE_RIGHT ] ){
        //ship.movement = movement::UP_RIGHT;
    }else if( ks[ SDL_SCANCODE_DOWN ] && ks[ SDL_SCANCODE_RIGHT ] ){
        //ship.movement = movement::DOWN_RIGHT;
    }else if( ks[ SDL_SCANCODE_DOWN ] && ks[ SDL_SCANCODE_LEFT ] ){
        //ship.movement = movement::DOWN_LEFT;
    }else if( ks[ SDL_SCANCODE_UP ] ){
        player.movement_state = movement_states::UP;        
    }else if( ks[ SDL_SCANCODE_DOWN ] ){ 
        player.movement_state = movement_states::DOWN;           
    }else if( ks[ SDL_SCANCODE_LEFT ] ){ 
        player.movement_state = movement_states::LEFT;        
    }else if( ks[ SDL_SCANCODE_RIGHT ] ){
        player.movement_state = movement_states::RIGHT;
    }
    
    // action buttons
    if( ks[ SDL_SCANCODE_Z ] ){
        // jump
        player.jump = true;
    }else if( ks[ SDL_SCANCODE_X ] ){        
        // Throw seed        
        player.seed_thrown = true;
    }
    
    // camera movement
    if( ks[ SDL_SCANCODE_K ] ){
        camera.x -= 4;
    }else if( ks[ SDL_SCANCODE_L ] ){        
        camera.x += 4;
    }
    
    
}


void MainGame::draw(){
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF ); 
    SDL_RenderClear( renderer );
    
    drawWorld();
    drawObjects();
    drawCharacters();
    
    SDL_RenderPresent( renderer );
}

void MainGame::drawWorld(){    
    
    // Draw everthing in viewport
    //SDL_Rect viewport = { 0, 0, 300, 300 };
    int block_size = 64;

    lua_getglobal( lua, "cameraLayout" );
    lua_pushinteger( lua, camera.x );
    lua_pushinteger( lua, camera.y );
    lua_pushinteger( lua, camera.w );
    lua_pushinteger( lua, camera.h );
    if( lua_pcall( lua, 4, 1, 0 ) != 0 ){
        lua_error( lua );            
    }    
    // Returned value is in the stack    

    lua_pushnil( lua );
    while( lua_next( lua, -2 ) != 0 ){         
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        
        int index = lua_gettop( lua );       
        lua_rawgeti( lua, index, 1 );
        lua_rawgeti( lua, index, 2 );
        lua_rawgeti( lua, index, 3 );
        lua_rawgeti( lua, index, 4 );
        lua_rawgeti( lua, index, 5 );
        srcrect = sprites[ lua_tostring( lua, -5 ) ];
        dstrect.x = lua_tointeger( lua, -4 ) * block_size;
        dstrect.y = lua_tointeger( lua, -3 ) * block_size;
        dstrect.w = block_size;
        dstrect.h = block_size;
        
        for( int i = 0; i < lua_tointeger( lua, -2 ); i++ ){
            dstrect.x = ( lua_tointeger( lua, -4 ) + i ) * block_size;
            dstrect.x -= camera.x; // TODO            
            
            for( int j = 0; j < lua_tointeger( lua, -1 ); j++ ){                
                dstrect.y = ( lua_tointeger( lua, -3 ) + j ) * block_size;   
                dstrect.y -= camera.y; // TODO
                SDL_RenderCopy( renderer, spritesheet_world, &srcrect, &dstrect );                
            }
            SDL_RenderCopy( renderer, spritesheet_world, &srcrect, &dstrect );
        }
        lua_pop( lua, 5 );
        
        
       
        lua_pop( lua, 1 );
    }   
    
    lua_pop( lua, 1 ); 
    
        
}


void MainGame::drawObjects(){
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    
    
    for( auto element : world_objects ){
        srcrect = sprites[ element.first ];
        dstrect.x = element.second.x - camera.x;
        dstrect.y = element.second.y - camera.y;
        dstrect.w = 21;
        dstrect.h = 32;
        SDL_RenderCopy( renderer, spritesheet_world, &srcrect , &dstrect );
    }
}

void MainGame::drawCharacters(){
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    
    
    if( player.state == sprite_states::RIGHT ){
        srcrect = sprites[ "Terra_test1" ];
    }else if( player.state == sprite_states::LEFT ){
        srcrect = sprites[ "Terra_test2" ];
    }
    
    
    dstrect.x = player.xpos - camera.x;
    dstrect.y = player.ypos - camera.y;
    dstrect.w = 64;
    dstrect.h = 64;
    
    
    SDL_RenderCopy( renderer, spritesheet_characters, &srcrect , &dstrect );
}


















