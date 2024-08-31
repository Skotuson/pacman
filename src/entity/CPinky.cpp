#include "CPinky.hpp"

const size_t PINKY_OFFSET = 4;

CPinky::CPinky ( size_t x, size_t y, char look, std::string color ) 
: CGhost ( x, y, look, color )
{}
        
void CPinky::scatter ( void ) {
    m_ANSI_color = m_ANSI_origColor;
    m_TargetX = 0;
    m_TargetY = ghostMaxScatterY;
}

void CPinky::chase ( CPacman & pacman ) {
    if ( ghostStrategy == RABID ) {
        rabidChase( pacman );
        return;
    }
    switch ( pacman . getDirection() ) {
        case UP:
            m_TargetX = pacman . getX() - PINKY_OFFSET;
            m_TargetY = pacman . getY() - PINKY_OFFSET;
            break;
        case DOWN:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY() + PINKY_OFFSET;
            break;
        case LEFT:
            m_TargetX = pacman . getX() - PINKY_OFFSET;
            m_TargetY = pacman . getY();
            break;
        case RIGHT:
            m_TargetX = pacman . getX() + PINKY_OFFSET;
            m_TargetY = pacman . getY();
            break;
        case STATIONARY:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY();
            break;
    }
}