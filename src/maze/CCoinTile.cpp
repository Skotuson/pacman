#include "CCoinTile.hpp"

CCoinTile::CCoinTile ( char look, std::string color )
: CEmptyTile ( look, color )
{}

bool CCoinTile::isPassable ( void ) {
    return true;
}

Action CCoinTile::interact ( CEntity & entity ) {
    if ( hasCoin && entity . isPacman() ) {
        hasCoin = false;
        m_Look = ' ';
        return COIN;
    } return NONE;
}