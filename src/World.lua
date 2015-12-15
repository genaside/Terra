-- point(x,y)

world = {} 

-- multimedia
world.background_image = "./assets/images/background_world.png"

-- Sprite sheets are already loaded, so just define position
world.block_types = {
    water = {
        x = 0, y = 0, w = 64, h = 64
    },    
    earth = {
        x = 64, y = 0, w = 64, h = 64
    }
}


world.block_size = 64
-- world.tile_size = { width = 64, height = 64 }
-- TODO
world.width = 50 * world.block_size
world.height = 50 * world.block_size






-- { block_type, x, y, number of blocks on x, number of blocks on y}
-- world coodinates
-- NOTE dont use 0 for w or h.
world.layout = {
    { "earth", 0, 3, 1, 7 }, { "earth", 1, 7, 8, 1 }, { "earth", 8, 5, 2, 3 }, { "earth", 11, 7, 5, 1 }, { "earth", 12, 7, 1, 1 }
    --{ "earth", 0, 3, 1, 50 }, { "earth", 11, 3, 1, 50 }, { "earth", 12, 3, 1, 50 }
}











-- Functions
function getWorldLayout()
    temp_layout = {}
    
    temp_layout = world.layout
    
    return temp_layout
end

-- get layout for 
function cameraLayout( x, y, w, h )
    temp_layout = {}
    
    for k, v in pairs( world.layout ) do
        -- If somewhat inside camera's view, store it
        if (v[3] * world.block_size) < (y + h) and
            (v[2] * world.block_size) < (x + w) and
            (v[2] * world.block_size) + world.block_size > x
        then
            table.insert( temp_layout, v )
        end
    end
    
    
    
    --return temp_layout
    return world.layout
end



function isOutsideWorld( x, y, w, h )
    
end

-- check if a rect is passing a object that is not passable
function isNonPassable( x, y, w, h )
    for k, v in pairs( world.layout ) do
        if v[1] == "earth" then
            -- test bondry
            if (y + h) > (v[3] * world.block_size) and 
               y < (v[3] * world.block_size) + (world.block_size * v[5]) and 
               (x + w) > (v[2] * world.block_size) and 
               x < ( v[2] * world.block_size ) + (world.block_size * v[4])  
            then
                return true
            else
                --return false
            end
        end
    end
    return false
end


--print( isNonPassable( 100 , 0, 64, 64 ) )
















