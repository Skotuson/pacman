#ifndef CGAME_H
#define CGAME_H

#include <string>
#include <vector>
#include "../maze/CMaze.hpp"
#include "../entity/CGhost.hpp"

#include "CConfig.hpp"
#include "CController.hpp"
#include "CRender.hpp"

enum GhostState { SCATTER, CHASE, FRIGHTENED };

const char EXIT_GAME = 'x';

/**
 * \mainpage
 * # Simple pacman in your console.  
 * 
 * ## Menu controls:  
 * play - Starts a new game  
 * exit - Exits game  
 *
 * ## Choosing map controls:  
 * exit - Exits game  
 *
 * ## In-game Pacman controls:  
 * w - Sets Pacman's direction Up  
 * s - Sets Pacman's direction Down  
 * d - Sets Pacman's direction Right  
 * a - Sets Pacman's direction Left  
 * x - Exits game ( only works when in-game )  
 *
 * ## Maze file format:  
 * <rows> <cols> <scatter timer> <chase timer> <frighten timer> <death timer> <gamemode>  
 * <maze representation>  
 * 
 * Example:  
 * 5 7 25 25 25 25 0  
 * <pre>
 * #######  
 * #ccccc#  
 * TeexeeT  
 * #1234p#  
 * #######
 * </pre>  
 * ## Where:
 * <pre>
 * e - Empty Tile  
 * c - Coin Tile  
 * # - Wall Tile  
 * T - Teleport Tile  
 * p - Pellet Tile  
 * x - Pacman's starting position  
 * 1 - Blinky type ghost starting position.  
 * 2 - Pinky type ghost starting position.  
 * 3 - Inky type ghost starting position.  
 * 4 - Clyde type ghost starting position.  
 * </pre>  
 * ## Maze Param Constraints:
 * - Rows, cols, timers and gamemode must be numeric values.  
 * - Number of rows and cols must match maze representation.  
 * - Rows and cols have a **50** limit, while the timers have **250** limit.  
 * - Timer values are the number of cycles of the game loop, not seconds.  
 *
 * ## Each maze must have:  
 * - Atleast one coin.  
 * - Pacman's origin coords and only one Pacman.  
 * - Teleport count must be zero and/or divisible by two.  
 * - Teleport position must be on the maze edge.  
 *
 * ## Gamemodes
 * Gamemodes are set by the parameter in maze file.  
 * 0 - Classic mode - Ghosts chase pacman with different tactics.  
 * 1 - Rabid Chase mode - Ghost chase pacman directly.  
 */

/**
 *@brief Main class which provides a bridge between all working parts of the game,
 * i.e. initialization and destruction of game objects, processing input and rendering output.
 */
class CGame {
    public:
              CGame ( void ) = default;
            /**
             * @brief Resets terminal settings and deletes or dynamically allocated objects.
             */
             ~CGame ( void );
              CGame ( const CGame & src ) = delete; 
        /**
         * @brief Serves as the main game loop.
         * In short, game loop consists of three main parts:
         * 1) Process input
         * 2) Update game state
         * 3) Output
         */
        void run  ( void );
   
    private:
        /**
         * @brief First part of a gameloop - input processing.
         * @return True if no error has occured, false otherwise.
         */
        bool processInput ( void );
        /**
         * @brief Second part of a gameloop - game state update
         * @param[in] firstFrame Boolean to handle the first frame
         * @return true if no error has occured, false otherwise
         */
        bool updateGameState ( bool firstFrame );

        /**
         * @brief Third part of a gameloop - Output the changed state
         * @return True if no ending condition has occured (e.g. Pacmans death), false otherwise.
         */
        void output ( void );

        /**
         * @brief Initializes the game state by creating game objects and setting up the terminal.
         * @return true if no error has occured, false otherwise.
         */
        bool init ( void );

        /**
         * @brief Detects collision between Pacman and Ghosts.
         * @return true if hit occured, false otherwise.
         */
        bool detectCollision ( void );

        /**
         * @brief Updates the game state according to the type of action on input.
         * @param[in] ac Action to handle.
         */
        void handleAction ( Action ac );

        /**
         * @brief Decrements timer of current game state
         */
        void decrementTimer ( void );

        /**
         * @brief Checks if the current game state timer is zero.
         * @return true if timer is zero, false otherwise
         */
        bool isTimerZero ( void );

        /**
         * @brief Provides a reaction according to the current ghost state
         */
        void handleGhostState ( void );

        /**
         * @brief Sets ghost state according to timer.
         */
        void updateGhostState ( void );

        /**
         * @brief Sets ghost state.
         * @param[in] gs Ghost state to be set.
         */
        void updateGhostState ( GhostState gs );

        size_t      m_Coins,
                    m_CurrentTimer;
        GhostState  m_CurrState = CHASE;

        CConfig     m_Config;
        CController m_Controller;
        CRender     m_Render;
        
        CPacman   * m_Pacman;
        CMaze     * m_Maze;
        std::vector <CGhost*> m_Ghosts;
};

#endif