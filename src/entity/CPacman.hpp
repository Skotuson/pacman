#ifndef CPACMAN_H
#define CPACMAN_H

#include "CEntity.hpp"

/**
 @brief Represents the player character
*/
class CPacman : public CEntity {
    public:
              /**
               * @param x Origin X coord
               * @param y Origin Y coord
               * @param look Entity character representation
               * @param color ANSI sequence which colors terminal
               */
             CPacman        ( size_t x, 
                              size_t y, 
                              char look, 
                              std::string color );
        
        /**
         * @brief Checks if an entity is Pacman
         * @return True if entity is Pacman, false otherwise
         */
        virtual bool isPacman ( void ) override;

        /**
         * @brief Sets Pacman direction according to keyboard input
         * @param keyboardInput Last character input from keyboard.
         */
        void handleControls ( char keyboardInput );
};

#endif