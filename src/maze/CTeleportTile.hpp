#ifndef CTELEPORT_TILE_H
#define CTELEPORT_TILE_H

#include "CEmptyTile.hpp"
#include "../game/CGeometry.hpp"
#include <string>

/**
 * @brief Class which represents a tile which has teleport entrance on it.
 */
class CTeleportTile : public CEmptyTile {
    public:
                       CTeleportTile  ( char look, 
                                        std::string color, 
                                        size_t x, 
                                        size_t y, 
                                        Direction d );
                       
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
               /**
                * @brief Sets the exit coords
                */  
                void   setExit      ( CTeleportTile & t );
    private:
        size_t    m_ExitX, m_ExitY,
                  m_EntrX, m_EntrY;
        Direction m_EntrDir,
                  m_ExitDir;

};

#endif