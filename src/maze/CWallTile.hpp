#ifndef CWALL_TILE_H
#define CWALL_TILE_H

#include "CEmptyTile.hpp"
#include <string>

/**
 * @brief Class which represents a tile which has wall on it.
 */
class CWallTile : public CEmptyTile {
    public:
                       CWallTile  ( char look, std::string color );
                       
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
};

#endif