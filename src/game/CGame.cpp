#include "CGame.hpp"
#include <iostream>

CGame::~CGame ( void ) {
    m_Render     . showCursor     ( std::cout );
    m_Controller . restoreTerminal();

    delete m_Pacman;
    for ( const auto & g : m_Ghosts )
        delete g;
    delete m_Maze;

    std::cout << std::endl;
}

bool CGame::init ( void ) {
    m_Render . clearScreen ( std::cout );
    int r;
    bool printHead = true;
    while ( ! ( r = m_Controller . handleMenu( printHead ) ) ) {
        printHead = false;
        m_Render . clearScreen ( std::cout );
        std::cout << "Invalid choice, please try again: " << std::endl;
    }
    if ( r == -1 )
        return false;

    std::string   filename;
    std::ifstream ifs;
    bool openErr = false;

    do {
        m_Render . clearScreen ( std::cout );
        if ( openErr )
            std::cout << "Invalid file!" << std::endl;
        std::cout << ANSI_CLEAR_LINE << "Enter filename: "; 
        if ( ! m_Controller . readLine ( std::cin, filename ) || filename == "exit" )
            return false;
        openErr = true;
    } while ( ! m_Config . openFile ( filename, ifs ) );

    m_Pacman = new CPacman ( 0, 0, 'C', ANSI_COLOR_YELLOW );
    
    if ( ! m_Config . loadGame ( ifs, m_Maze, m_Pacman, &m_Ghosts, m_Coins ) ) {
        m_Config . printErr( std::cout );
        return false;
    }

    m_Render     . clearScreen      ( std::cout );
    m_Render     . hideCursor       ( std::cout );

    m_Controller . setUpTerminal    ();
    m_Controller . toggleBlockingIO ();        
    return true;
}

/*
* Game Loop: 
* 1) Process input
* 2) Update game state
* 3) Output
*/
void CGame::run ( void ) {
    if ( init() ) {
        bool firstFrame = true;
        while ( m_Coins && processInput() && updateGameState( firstFrame ) ) {
        output();
        firstFrame = false;
        }
        if ( !m_Coins )
            std::cout << "Congratulations, you win!" << std::endl;
        else {
            output();
        }
    }
}

bool CGame::processInput ( void ) {
    m_Controller . readInput();
    char keyboardInput = m_Controller . getKeyboardInput();
    if ( keyboardInput != EXIT_GAME )
        m_Pacman -> handleControls( m_Controller . getKeyboardInput() );
    else return false;
    return true;
}

bool CGame::updateGameState ( bool firstFrame ) {
    if ( firstFrame )
        return true;

    if ( isTimerZero() )
        updateGhostState();

    handleGhostState();
    decrementTimer();

    if ( detectCollision() )
        return false;

    Action ac;
    if ( m_Maze -> canEntityMove ( *m_Pacman, m_Pacman -> getDirection() ) )
        m_Pacman -> move();
    ac = m_Maze -> at ( m_Pacman -> getX(), m_Pacman -> getY() ) . interact( *m_Pacman );
    handleAction ( ac );

    if ( detectCollision() )
        return false;

    for ( size_t i = 0; i < m_Ghosts . size(); i++ ) {
        if ( m_Ghosts[i] -> isDead() ) 
            continue;
        m_Maze -> at ( m_Ghosts[i] -> getX(), m_Ghosts[i] -> getY() ) . interact( *m_Ghosts[i] );
        m_Ghosts[i] -> setDirection( m_Maze -> getQuickestDir ( *m_Ghosts[i] ) );
        m_Ghosts[i] -> move();
        }  
    return true;
}

void CGame::output ( void ) {
    m_Render . returnCursor ( std::cout );
    std::cout << ANSI_CLEAR_LINE << "Coins left: " << m_Coins << std::endl;
    std::cout << *m_Maze;
    usleep ( MSECONDS_SLEEP );
}

void CGame::handleAction ( Action ac ) {
    switch ( ac ) {
        case NONE:
            break;
        case COIN:
            m_Coins--;
            break;
        case PELLET:
            updateGhostState ( FRIGHTENED );
            break;
        case TELEPORT:
            m_Controller . overrideKeyboardIn ( m_Pacman -> getDirection() );
            break;
    }
}

bool CGame::detectCollision ( void ) {
    for ( const auto & g : m_Ghosts ) {
        if ( g -> isAt( m_Pacman -> getX(), m_Pacman -> getY() ) && ! g -> isDead() ) {
            if ( m_CurrState == FRIGHTENED ) {
                g -> kill();
                return false; 
            }
            std::cout << ANSI_CLEAR_LINE << "You were killed by: " << *g << std::endl;
            return true;
        } 
    }
    return false;
}

void CGame::decrementTimer ( void ) {
    m_CurrentTimer--;
}

bool CGame::isTimerZero ( void ) {
    return ! m_CurrentTimer;
}

void CGame::handleGhostState ( void ) {
    for ( const auto & g : m_Ghosts ) {
        if ( g -> isDead() )
            g -> attemptRespawn();
        switch ( m_CurrState ) {
           case SCATTER:
               g -> scatter();
               break;
           case CHASE:
               g -> chase( *m_Pacman );
               break;
           case FRIGHTENED:
               g -> frighten( *m_Pacman );
               break;
         }
    }
}

void CGame::updateGhostState ( void ) {
    switch ( m_CurrState ) {
        case SCATTER:
            m_CurrState = CHASE;
            m_CurrentTimer = m_Config . getChaseTimer();
            break;
        case CHASE:
        case FRIGHTENED:
            m_CurrState = SCATTER;
            m_CurrentTimer = m_Config . getScatterTimer();
            break;
    }
}

void CGame::updateGhostState ( GhostState gs ) {
    switch ( gs ) {
        case SCATTER:
            m_CurrState = SCATTER;
            m_CurrentTimer = m_Config . getScatterTimer();
            break;
        case CHASE:
            m_CurrState = CHASE;
            m_CurrentTimer = m_Config . getChaseTimer();
            break;
        case FRIGHTENED:
            m_CurrState = FRIGHTENED;
            m_CurrentTimer = m_Config . getFrightenedTimer();
            break;
    }
}
