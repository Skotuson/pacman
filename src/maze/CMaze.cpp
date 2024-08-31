#include "CMaze.hpp"

CMaze::CMaze ( size_t r, size_t c, CPacman * pacman, std::vector<CGhost*> * ghosts ) 
: m_R ( r ),
  m_C ( c ), 
  m_Pacman ( pacman ),
  m_Ghosts ( ghosts )
{
    m_Tiles = new CEmptyTile** [m_R];
    for ( size_t i = 0; i < m_R; i++ ) {
        m_Tiles[i] = new CEmptyTile* [m_C];
        for ( size_t j = 0; j < m_C; j++ )
            m_Tiles[i][j] = new CEmptyTile();
    }
}

CMaze::~CMaze ( void ) {
    for ( size_t i = 0; i < m_R; i++ ) {
        for ( size_t j = 0; j < m_C; j++ )
            delete m_Tiles[i][j];
        delete [] m_Tiles[i];
    }
    delete [] m_Tiles;
}

void CMaze::put ( size_t x, size_t y, CEmptyTile * tile ) {
    delete m_Tiles[y][x];
    m_Tiles[y][x] = tile;
}

CEmptyTile & CMaze::at ( size_t x, size_t y ) {
    return *(m_Tiles[y][x]);
}

bool CMaze::canEntityMove ( CEntity & entity, Direction dir ) {
    size_t x = entity . getX(), y = entity . getY();
    switch ( dir ) {
        case UP:
            return y && m_Tiles[y - 1][x] -> isPassable();
        case DOWN:
            return y < m_R - 1 && m_Tiles[y + 1][x] -> isPassable();
        case LEFT:
            return x && m_Tiles[y][x - 1] -> isPassable();
        case RIGHT:
            return x < m_C - 1 && m_Tiles[y][x + 1] -> isPassable();
        default:
            return false;
    }
    return false;
}

Direction CMaze::getQuickestDir ( CGhost & g ) {
    Direction quickest = STATIONARY;
    bool isMinSet = false;
    int minDist = 0;
    for ( int dir = UP; dir != NO_DIRECTIONS; dir++ ) {
        if ( dir == CGeometry::getOppositeDir ( g . getDirection() ) )
            continue;
        Direction d = static_cast<Direction>(dir);
        int x = g . getX(), y = g . getY();
        CGeometry::shiftCoords ( x, y, d );
        if ( canEntityMove ( g, d ) ) {
           int dist = CGeometry::calculateDist ( x, y, g . getTargetX(), g . getTargetY() );
            if ( dist < minDist || !isMinSet ) {
                minDist  = dist;
                quickest = d;
                isMinSet = true;
            }
        }
    }
    return quickest;
}

void CMaze::drawTile ( std::ostream & os, size_t x, size_t y ) const {
    for ( size_t i = 0; i < m_Ghosts -> size(); i++ )
        if ( ! m_Ghosts -> at(i) -> isDead() && m_Ghosts -> at(i) -> isAt ( x, y ) ) {
            os << *m_Ghosts -> at(i);
            return;
    }

    if ( m_Pacman -> isAt ( x, y ) ) {
        os << *m_Pacman;
        return;
    }

    os << *m_Tiles[y][x];
}

std::ostream & operator << ( std::ostream & os, const CMaze & maze ) {
    for ( size_t i = 0; i < maze . m_R; i++ ) {
      for ( size_t j = 0; j < maze . m_C; j++ )
        maze . drawTile ( os, j, i );
      os << std::endl;
    }
    return os;
}