#ifndef CGEOMETRY_H
#define CGEOMETRY_H

#include "Direction.hpp"
#include <cstdlib>

/**
 * @brief Library class which contains functions to work with coords and directions.
 */
class CGeometry {
    public:
        static int          calculateDist  ( size_t x, size_t y, size_t targetX, size_t targetY );
        /**
         * @brief Calculates distance between two points according to Pacman rules.
         * @param[out] x Output param of shifted X coord.
         * @param[out] y Output param of shifted Y coord.
         * @param[in] d Direction in which the point will be shifted.
         */
        static void         shiftCoords    ( int & x, int & y, Direction d );
        /**
         * @brief Returns the opposite direction.
         * @param[in] d Direction to find the opposite to
         */
        static Direction    getOppositeDir ( Direction d );
};

#endif