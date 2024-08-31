#ifndef CCOIN_TILE_H
#define CCOIN_TILE_H

#include "CEmptyTile.hpp"
#include <string>

/**
 * @brief Class which represents a tile which has coin on it.
 */
class CCoinTile : public CEmptyTile {
    public:
                       CCoinTile  ( char look, std::string color );
        /**
         * @brief Determines if the tile is passable
         * @return True if tile is passable, false otherwise.
         */      
        virtual bool   isPassable ( void );
        /**
         * @brief Provides tile interaction with the entity
         * @param entity Entity which stepped on the tile.
         * @return Action depending on the tile.
         */
        virtual Action interact   ( CEntity & entity ); 
    private:
        bool hasCoin = true;
};

#endif