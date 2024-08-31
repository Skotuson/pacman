#ifndef CEMPTY_TILE_H
#define CEMPTY_TILE_H

#include "../game/CRender.hpp"
#include "../entity/CEntity.hpp"
#include <ostream>

enum Action { NONE, COIN, PELLET, TELEPORT };

/**
 * @brief Class which represents an empty tile, also serves as a base class for all other tiles.
 */
class CEmptyTile {
    public:
                       CEmptyTile  ( char look = ' ', 
                                     std::string color = ANSI_COLOR_DEFAULT );
        virtual        ~CEmptyTile ( void ) = default;
        /**
         * @brief Determines if the tile is passable
         * @return True if tile is passable, false otherwise.
         */
        virtual bool   isPassable  ( void );
        /**
         * @brief Provides tile interaction with the entity
         * @param entity Entity which stepped on the tile.
         * @return Action depending on the tile.
         */
        virtual Action interact    ( CEntity & entity ); 

        friend std::ostream & operator << ( std::ostream & os, const CEmptyTile & tile );
    protected:
        char m_Look;
        std::string m_ANSI_color;
};

#endif