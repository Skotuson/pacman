#include "CBlinky.hpp"

CBlinky::CBlinky ( size_t x, size_t y, char look, std::string color ) 
: CGhost ( x, y, look, color )
{}
        
void CBlinky::scatter ( void ) {
    m_ANSI_color = m_ANSI_origColor;
    m_TargetX = m_TargetY = 0;
}

void CBlinky::chase ( CPacman & pacman ) {
    rabidChase( pacman );
}