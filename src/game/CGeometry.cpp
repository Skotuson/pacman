#include "CGeometry.hpp"

int CGeometry::calculateDist ( size_t x, size_t y, size_t targetX, size_t targetY ) {
    int distX = abs( x - targetX ), distY = abs ( y - targetY );
    return distX * distX + distY * distY;
}

Direction CGeometry::getOppositeDir ( Direction d ) {
    switch ( d ) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        case STATIONARY:
            return STATIONARY;
    }
    return STATIONARY;
}

void CGeometry::shiftCoords ( int & x, int & y, Direction d ) {
    switch ( d ) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case STATIONARY:
            break;
    }
}