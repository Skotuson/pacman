#include "CEntity.hpp"
#include "../game/CRender.hpp"

 CEntity::CEntity ( size_t x, size_t y, char look, std::string color )
 :  m_X              ( x ),
    m_Y              ( y ),
    m_OriginX        ( x ),
    m_OriginY        ( y ),
    m_Look           ( look ),
    m_ANSI_color     ( color ),
    m_ANSI_origColor ( color )
 {}

bool CEntity::isAt ( size_t x, size_t y ) {
    return m_X == x && m_Y == y;
}

void CEntity::setDirection ( char keyboardInput ) {
    switch ( keyboardInput ) {
        case 'w':
            m_Direction = UP;
            break;
        case 's':
            m_Direction = DOWN;
            break;
        case 'd':
            m_Direction = RIGHT;
            break;
        case 'a':
            m_Direction = LEFT;
            break;
    }
}

void CEntity::setDirection ( Direction dir ) {
    m_Direction = dir;
}

Direction CEntity::getDirection ( void ) {
    return m_Direction;
}

void CEntity::move ( void ) {
    switch ( m_Direction ) {
        case STATIONARY:
            break;
        case UP:
            m_Y--;
            break;
        case DOWN:
            m_Y++;
            break;
        case LEFT:
            m_X--;
            break;
        case RIGHT:
            m_X++;
            break;
    }
}

void CEntity::setX ( size_t x ) {
    m_X = x;
}

void CEntity::setY ( size_t y ) {
    m_Y = y;
}

size_t CEntity::getX ( void ){
    return m_X;
}

size_t CEntity::getY ( void ){
    return m_Y;
}


std::ostream & operator << ( std::ostream & os, const CEntity & entity ) {
    os << entity . m_ANSI_color << entity . m_Look << ANSI_COLOR_DEFAULT;
    return os;
}