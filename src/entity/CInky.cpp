#include "CInky.hpp"

const size_t INKY_OFFSET = 2;

CInky::CInky ( size_t x, size_t y, char look, std::string color ) 
: CGhost ( x, y, look, color )
{}
        
void CInky::scatter ( void ) {
    m_ANSI_color = m_ANSI_origColor;
    m_TargetX = ghostMaxScatterX;
    m_TargetY = 0;
}

void CInky::chase ( CPacman & pacman ) {
    if ( ghostStrategy == RABID ) {
        rabidChase( pacman );
        return;
    }
    switch ( pacman . getDirection() ) {
        case UP:
            m_TargetX = pacman . getX() - INKY_OFFSET;
            m_TargetY = pacman . getY() - INKY_OFFSET;
            break;
        case DOWN:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY() + INKY_OFFSET;
            break;
        case LEFT:
            m_TargetX = pacman . getX() - INKY_OFFSET;
            m_TargetY = pacman . getY();
            break;
        case RIGHT:
            m_TargetX = pacman . getX() + INKY_OFFSET;
            m_TargetY = pacman . getY();
            break;
        case STATIONARY:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY();
            break;
    }
}