#ifndef CMAZE_H
#define CMAZE_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include "../game/Direction.hpp"
#include "../entity/CGhost.hpp"
#include "../entity/CPacman.hpp"
#include "../game/CGeometry.hpp"
#include "CEmptyTile.hpp"

/**
 * @brief Maze class which holds information about tiles and their state.
 * Also handles Pacman and Ghost movements.
 */
class CMaze {
    public:
            /**
             * @param r Number of maze rows
             * @param c Number of maze cols
             * @param pacman Pacman instance associated with current maze
             * @param ghosts Ghost instances associated with current maze
             */
             CMaze                  ( size_t r, 
                                      size_t c, 
                                      CPacman * pacman, 
                                      std::vector<CGhost*> * ghosts );
             ~CMaze                 ( void );

        /**
         * @brief Yields the maze tile at (x,y) coords.
         * @param x X coordinate
         * @param y Y coordinate
         * @return Reference to found tile
         * TODO: error handling
         */
        CEmptyTile & at             ( size_t x, size_t y );
        /**
         * @brief Puts the CEmptyTile pointer at (x,y) coords.
         * @param x X coordinate
         * @param y Y coordinate
         * @param tile Tile to be placed into the maze
         * TODO: error handling
         */
        void         put            ( size_t x, size_t y, CEmptyTile * tile );
        /**
         * @brief Displays maze tile.
         * @param os Output stream on which the tile will be displayed.
         * @param x X coordinate
         * @param y Y coordinate
         * TODO: error handling
         */
        void         drawTile       ( std::ostream & os, size_t x, size_t y ) const;
        /**
         * @brief Determines if an entity can move in selected direction.
         * @param entity Entity which will be moved.
         * @param dir Direction in which the entity is currently heading.
         * @return true if the entity can move in selected direction, false otherwise.
         */
        bool         canEntityMove  ( CEntity & entity, Direction dir );
        /**
         * @brief Returns a direction in which the ghost will approach its target the quickest.
         * @param g Ghost which will be moved.
         * @return Direction which leads to its target the quickest based on its current position and game rules.
         */
        Direction    getQuickestDir ( CGhost & g );
        
        friend std::ostream & operator << ( std::ostream & os, const CMaze & maze );
    
    private:
        size_t         m_R, m_C;
        CEmptyTile *** m_Tiles;
        CEntity      * m_Pacman;
        std::vector<CGhost*> * m_Ghosts;
};

#endif