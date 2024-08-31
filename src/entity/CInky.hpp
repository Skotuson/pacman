#ifndef CINKY_H
#define CINKY_H

#include "CGhost.hpp"

/**
 @brief Represents a ghost which tries to get ahead of Pacman
*/
class CInky : public CGhost {
    public:
            /**
             * @param x Origin X coord
             * @param y Origin Y coord
             * @param look Entity character representation
             * @param color ANSI sequence which colors terminal
             */
             CInky           ( size_t x, size_t y, char look, std::string color );
        
        /**
         * @brief Sets the Ghost target coords relative to pacman, according to the ghost type.
         * @param pacman Pacman to chase
         */     
        virtual void chase           ( CPacman & pacman ) override;
        /**
         * @brief Sets the Ghost target coords to their scatter location, differs by the ghost type.
         */    
        virtual void scatter         ( void ) override;
    private:

};

#endif