#ifndef CPELLET_TILE_H
#define CPELLET_TILE_H

#include "CEmptyTile.hpp"
#include <string>

/**
 * @brief Class which represents a tile which has power pellet on it.
 */
class CPelletTile : public CEmptyTile {
    public:
                       CPelletTile ( char look, std::string color );
                       
        /**
         * @brief Determines if the tile is passable
         * @return True if tile is passable, false otherwise.
         */
        virtual bool   isPassable  ( void );
        /**
         * @brief Determines if the tile is passable
         * @return True if tile is passable, false otherwise.
         */  
        virtual Action interact    ( CEntity & entity ); 
    private:
        bool hasPellet = true;
};


#endif