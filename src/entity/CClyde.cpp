#include "CClyde.hpp"
#include "../game/CGeometry.hpp"

const int CLYDE_OFFSET = 8;

CClyde::CClyde ( size_t x, size_t y, char look, std::string color ) 
: CGhost ( x, y, look, color )
{}
        
void CClyde::scatter ( void ) {
    m_ANSI_color = m_ANSI_origColor;
    m_TargetX = ghostMaxScatterX;
    m_TargetY = ghostMaxScatterY;
}

void CClyde::chase ( CPacman & pacman ) {
    if ( ghostStrategy == RABID )
        rabidChase( pacman );
    else if ( CGeometry::calculateDist ( m_X, m_Y, pacman . getX(), pacman . getY() ) >= CLYDE_OFFSET ) {
        m_TargetX = pacman . getX();
        m_TargetY = pacman . getY();
    } else scatter();
}