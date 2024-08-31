#include "CEmptyTile.hpp"

CEmptyTile::CEmptyTile ( char look, std::string color ) 
: m_Look       ( look ),
  m_ANSI_color ( color )
{}

bool CEmptyTile::isPassable ( void ) {
    return true;
}

Action CEmptyTile::interact ( CEntity & entity ) {
    return NONE;
}

std::ostream & operator << ( std::ostream & os, const CEmptyTile & tile ) {
    os << tile . m_ANSI_color << tile . m_Look << ANSI_COLOR_DEFAULT;
    return os;
}