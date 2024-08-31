#include "CController.hpp"

ssize_t CController::readInput ( void ) {
    return read ( 0, input, BUFFER_SIZE );
}

int CController::handleMenu ( bool printHead ) {
    if ( printHead )
        std::cout << "Welcome to " << ANSI_COLOR_YELLOW << "PaCman" 
                                   << ANSI_COLOR_DEFAULT << std::endl;
    
    std::cout << "[play] New Game" << std::endl;
    std::cout << "[exit] Exit" << std::endl;
    std::cout << "Your choice: ";
    std::string opt;

    if ( ! ( std::cin >> opt ) ) {
        if ( std::cin . eof() )
            return -1;
        return 0;
    }
    if ( opt == "play" ) return 1;
    else if ( opt == "exit" ) return -1; 
    return 0;
}

bool CController::readLine ( std::istream & is, std::string & lineBuffer ) {
    if ( std::getline( is >> std::ws, lineBuffer ) )
        return true;
    return false;
}

char CController::getKeyboardInput ( void ) {
    return input[0];
}

void CController::setUpTerminal ( void ) {
    struct termios t;
    tcgetattr ( STDIN_FILENO, &t );
    if ( ! origSet ) {
        terminalOrig = t.c_lflag;
        origSet = true;
    }
    t . c_lflag &= ~(ICANON|ECHO);
    tcsetattr ( STDIN_FILENO, TCSANOW, &t );
}

void CController::restoreTerminal ( void ) {
    struct termios t;
    tcgetattr ( STDIN_FILENO, &t );
    t . c_lflag |= ECHO | ICANON;
    tcsetattr ( STDIN_FILENO, TCSANOW, &t );
} 

void CController::toggleBlockingIO ( void ) {
    fcntl (0, F_SETFL, O_NONBLOCK);
}

void CController::overrideKeyboardIn ( Direction d ) {
    switch ( d ) {
        case UP:
            input[0] = 'w';
            break;
            
        case DOWN:
            input[0] = 's';
            break;
            
        case LEFT:
            input[0] = 'a';
            break;
            
        case RIGHT:
            input[0] = 'd';
            break;
            
        case STATIONARY:
            input[0] = '\0';
            break;
    }
}