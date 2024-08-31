#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include "CGeometry.hpp"
#include "CRender.hpp"
#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

const size_t BUFFER_SIZE = 25;

/**
 * @brief Provides input reading functions and I/O terminal settings related functions.
 */
class CController {
    public:
        /** 
         * @brief This function was inspired by the randomusername's answer on https://stackoverflow.com/questions/20588002/nonblocking-get-character.
         *  Reads bytes into buffer.
         * @return Returns a non-negative integer indicating the number of bytes read if successful,
                            -1 to indicate a error.
         */
        ssize_t readInput        ( void );
        /** 
         * @brief Prints out the game main menu and handles user input
         * @param[in] printHead Bool to decide if the Pacman header should be printed
         * @return 1 if choice is valid, 0 if erro has occured, -1 if the exit option was chosen
         */
        int     handleMenu       ( bool printHead );
        /** 
         * @brief Reads the next line from the input stream and saves it in to a buffer.
         * @param[out] is Input stream to read from
         * @param[out] lineBuffer String to store the read line
         * @return true if reading was success, false otherwise 
         */
        bool     readLine        ( std::istream & is, std::string & lineBuffer );
        /** 
         *@return The first character found in the input buffer.
         */
        char    getKeyboardInput ( void );
        /** 
         *@brief Toggles the blocking/non-blocking IO, inspired by the randomusername's answer on https://stackoverflow.com/questions/20588002/nonblocking-get-character.
         */
        void    toggleBlockingIO ( void );
        /** 
         *@brief Turns of terminal echoing and buffering.
         */
        void    setUpTerminal    ( void );
        /** 
         *@brief Restores default terminal settings.
         */
        void    restoreTerminal  ( void );
        /** 
         * @brief Sets the keyboard input from direction
         */
         void   overrideKeyboardIn ( Direction d );

    private:
        int  terminalOrig;
        bool origSet = false;
        char input[BUFFER_SIZE];
            
};

#endif