#include <cstdlib>
#include <ctime>
#include "CGhost.hpp"
#include "../game/CRender.hpp"

GhostStrategy CGhost::ghostStrategy;
size_t        CGhost::ghostMaxScatterX,
              CGhost::ghostMaxScatterY,
              CGhost::ghostDeathTimer;

CGhost::CGhost ( size_t x, size_t y, char look, std::string color ) 
: CEntity ( x, y, look, color )
{}

void CGhost::frighten ( CPacman & pacman ) {
    m_ANSI_color = ANSI_COLOR_B_BLUE;
    srand( time(0) );
    int randomOffset = ( rand() % GHOST_OFFSET ) + GHOST_OFFSET;
    switch ( pacman . getDirection() ) {
        case UP:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY() - randomOffset;
            break;
        case DOWN:
            m_TargetX = pacman . getX();
            m_TargetY = pacman . getY() + randomOffset;
            break;
        case LEFT:
            m_TargetX = pacman . getX() - randomOffset;
            m_TargetY = pacman . getY();
            break;
        case RIGHT:
            m_TargetX = pacman . getX() - randomOffset;
            m_TargetY = pacman . getY();
            break;
        case STATIONARY:
            m_TargetX = pacman . getX() + randomOffset;
            m_TargetY = pacman . getY() - randomOffset;
            break;
    }
}

void CGhost::rabidChase ( CPacman & pacman ) {
    m_TargetX = pacman . getX();
    m_TargetY = pacman . getY();
}

void CGhost::kill ( void ) {
    m_IsDead = true;
    deathTimer = ghostDeathTimer;
}

void CGhost::attemptRespawn ( void ) {
    if ( !deathTimer ) {
        m_IsDead = false;
        m_X = m_OriginX;
        m_Y = m_OriginY;
    } else deathTimer--;
}

bool CGhost::isDead ( void ) {
    return m_IsDead;
}

bool CGhost::isPacman ( void ) {
    return false;
}

int  CGhost::getTargetX ( void ) {
    return m_TargetX;
}

int  CGhost::getTargetY ( void ) {
    return m_TargetY;
}

        