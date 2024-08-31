#include "CTeleportTile.hpp"

CTeleportTile::CTeleportTile ( char look, std::string color, size_t x, size_t y, Direction d )
: CEmptyTile ( look, color ),
  m_EntrX    ( x ),
  m_EntrY    ( y ),
  m_EntrDir  ( d )
{}

bool CTeleportTile::isPassable ( void ) {
    return true;
}

Action CTeleportTile::interact ( CEntity & entity ) {
    entity . setX (m_ExitX);
    entity . setY (m_ExitY);
    entity . setDirection ( m_ExitDir );
    return TELEPORT;
}

void CTeleportTile::setExit ( CTeleportTile & t ) {
    m_ExitX   = t . m_EntrX;
    m_ExitY   = t . m_EntrY;
    m_ExitDir = CGeometry::getOppositeDir( t . m_EntrDir );
}