#include "CPelletTile.hpp"

CPelletTile::CPelletTile ( char look, std::string color )
: CEmptyTile ( look, color )
{}

bool CPelletTile::isPassable ( void ) {
    return true;
}

Action CPelletTile::interact ( CEntity & entity ) {
    if ( hasPellet && entity . isPacman() ) {
        hasPellet = false;
        m_Look = ' ';
        return PELLET;
    } return NONE;
}