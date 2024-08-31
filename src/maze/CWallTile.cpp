#include "CWallTile.hpp"

CWallTile::CWallTile ( char look, std::string color )
: CEmptyTile ( look, color )
{}

bool CWallTile::isPassable ( void ) {
    return false;
}

Action CWallTile::interact ( CEntity & entity ) {
    return NONE;
}