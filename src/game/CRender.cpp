#include "CRender.hpp"

void CRender::clearScreen ( std::ostream & os ) {
    os << ANSI_RETURN_CURSOR << ANSI_CLEAR_SCREEN;
}

void CRender::returnCursor ( std::ostream & os ) {
    os << ANSI_RETURN_CURSOR;
}

void CRender::showCursor ( std::ostream & os ){
    os << ANSI_SHOW_CURSOR;
}

void CRender::hideCursor ( std::ostream & os ){
    os << ANSI_HIDE_CURSOR;
}