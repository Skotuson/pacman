#include "CPacman.hpp"

CPacman::CPacman ( size_t x, size_t y, char look, std::string color ) 
: CEntity ( x, y, look, color )
{}

void CPacman::handleControls ( char keyboardInput ) {
    setDirection ( keyboardInput );
}

bool CPacman::isPacman ( void ) {
    return true;
}