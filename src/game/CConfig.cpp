#include "CConfig.hpp"
#include "CRender.hpp"
#include "../maze/CEmptyTile.hpp"
#include "../maze/CCoinTile.hpp"
#include "../maze/CWallTile.hpp"
#include "../maze/CPelletTile.hpp"
#include "../entity/CBlinky.hpp"
#include "../entity/CInky.hpp"
#include "../entity/CPinky.hpp"
#include "../entity/CClyde.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

bool CConfig::loadGame ( std::ifstream & ifs, CMaze *& maze, CPacman * pacman, 
                         std::vector<CGhost*> * ghosts, size_t & coins ) {
    if ( !(ifs >> std::skipws >> m_MazeRows >> m_MazeCols >> m_ScatterTimer 
               >> m_ChaseTimer >> m_FrightenedTimer >> CGhost::ghostDeathTimer >> m_GameMode) ) 
              {
                setErr ( "File Param Error: Non-numeric or missing!" );
                return false;
              }

    if ( ! validFileParams() ) {
        setErr ( "File Param Error: Values are not in allowed range!" );
        return false;
    }

    //set up config info for CGhost class
    CGhost::ghostStrategy    = static_cast<GhostStrategy>(m_GameMode);
    CGhost::ghostMaxScatterX = m_MazeCols;
    CGhost::ghostMaxScatterY = m_MazeRows;

    maze = new CMaze ( m_MazeRows, m_MazeCols, pacman, ghosts );
    CTeleportTile * t1 = nullptr, *t2 = nullptr;
    bool pacmanSet = false;

    std::string lineBuffer;
    size_t i = 0;
    while ( std::getline ( ifs >> std::ws, lineBuffer ) ) {
        if ( ! validRows ( i ) ) {
            setErr ( "Maze error: Wrong number of rows!" );
            return false;
        }
        
        for ( size_t j = 0; j < lineBuffer . length(); j++ ) {
            if ( ! validCols ( lineBuffer . length() ) ) {
                setErr ( "Maze error: Wrong number of columns!" );    
                return false;
            }

            char tileInfo = tolower( lineBuffer[j] );
            switch ( tileInfo ) {
                case 'c':
                case '#':
                case 'p':
                    addTile ( *maze, tileInfo, j, i, coins );
                    break;
                case 't':
                    if ( ! addTTile ( *maze, j, i, t1, t2 ) ) {
                        setErr ( "Maze error: Teleport has to be on the maze's edge!" );
                        return false;
                    }
                    break;
                case 'x':
                    if ( pacmanSet ) {
                        setErr ( "Maze error: Pacman has already been set!" );
                        return false;
                    }
                    pacmanSet = true;
                    pacman -> setX(j); pacman -> setY(i);
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                    addGhost ( *ghosts, tileInfo, j, i );
                    break;
            }
        } 
        i++;
    }
    
    if ( ! coins ) {
        setErr ( "Maze error: No coins placed!" );
        return false;
    }
    if ( ! pacmanSet ) {
        setErr ( "Maze error: Pacman is not set!" );
        return false;
    }
    //if there is less than m_MazeRows rows, it's an error
    if ( validRows ( i ) ) {
        setErr ( "Maze error: Wrong number of rows!" );
        return false;
    }
    if ( t1 ) {
        setErr ( "Maze error: Teleport is missing an exit!" );
        return false;
    }

    ifs . close();
    return true;
}

bool CConfig::openFile ( std::string filename, std::ifstream & ifs ) {
    ifs . open ( filename );
    return ! ifs . fail();
}

void CConfig::addTile ( CMaze & m, char c, size_t x, size_t y, size_t & coins ) {
    switch ( c ) {
        case 'c':
            m . put(x, y, new CCoinTile ( '.', ANSI_COLOR_B_YELLOW ));
            coins++;
            break;
        case '#':
            m . put(x, y, new CWallTile ( '#', ANSI_COLOR_BLUE ));
            break;
        case 'p':
            m . put(x, y, new CPelletTile ( 'o', ANSI_COLOR_WHITE ));
            break;
    }
}

bool CConfig::addTTile ( CMaze & m, size_t x, size_t y, CTeleportTile *& t1, CTeleportTile *& t2 ) {
    Direction d = determineTeleportEntryDir( x, y );
    if ( d == STATIONARY )
        return false;
    if ( ! t1 ) {
        t1 = new CTeleportTile ( '|', ANSI_COLOR_WHITE, x, y, d );
        m . put(x, y, t1);
    } 
    else {
        t2 = new CTeleportTile ( '|', ANSI_COLOR_WHITE, x, y, d );
        t1 -> setExit ( *t2 );
        t2 -> setExit ( *t1 );
        t1 = nullptr;
        m . put(x, y, t2);
    }
    return true;
}

void CConfig::addGhost ( std::vector<CGhost*> & g, char c, size_t x, size_t y ) {
    switch ( c ) {
        case '1':
            g . push_back ( new CBlinky ( x, y, '&', ANSI_COLOR_RED ) );
            break;
        case '2':
            g . push_back ( new CPinky ( x, y, '&', ANSI_COLOR_MAGENTA ) );
            break;
        case '3':
            g . push_back ( new CInky ( x, y, '&', ANSI_COLOR_CYAN ) );
            break;
        case '4':
            g . push_back ( new CClyde ( x, y, '&', ANSI_COLOR_B_GREEN ) );
            break;
    }
}

Direction CConfig::determineTeleportEntryDir ( size_t x, size_t y ) {
    if ( !x )
        return LEFT;
    if ( x == m_MazeCols - 1 )
        return RIGHT;
    if ( !y )
        return UP;
    if ( y == m_MazeRows - 1 )
        return DOWN;
    return STATIONARY;
}

size_t CConfig::getScatterTimer ( void ) {
    return m_ScatterTimer;
}

size_t CConfig::getChaseTimer ( void ) {
    return m_ChaseTimer;
}

size_t CConfig::getFrightenedTimer ( void ) {
    return m_FrightenedTimer;
}

bool CConfig::validCols ( size_t cols ) {
    return cols == m_MazeCols;
}

bool CConfig::validRows ( size_t rows ) {
    return rows < m_MazeRows;
}

void CConfig::setErr ( const std::string & err ) {
    m_Err = err;
}

void CConfig::printErr ( std::ostream & os ) {
    os << m_Err << std::endl;
}

bool CConfig::validFileParams ( void ) {
    return m_MazeRows <= MAX_DIM          && 
           m_MazeCols <= MAX_DIM          &&
           m_ScatterTimer <= MAX_TIMER    &&
           m_ChaseTimer   <= MAX_TIMER    &&
           m_FrightenedTimer <= MAX_TIMER &&
           ( !m_GameMode || m_GameMode == 1);
}