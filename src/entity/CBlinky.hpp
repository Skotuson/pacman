#ifndef CBLINKY_H
#define CBLINKY_H

#include "CPacman.hpp"
#include "CGhost.hpp"

/**
 @brief Represents a ghost which chases Pacman directly
*/
class CBlinky : public CGhost {
    public: 
            /**
             * @param[in] x Origin X coord
             * @param[in] y Origin Y coord
             * @param[in] look Entity character representation
             * @param[in] color ANSI sequence which colors terminal
             */
             CBlinky         ( size_t x, size_t y, char look, std::string color );
        
        /**
         * @brief Sets the Ghost target coords relative to pacman, according to the ghost type.
         * @param[in] pacman Pacman to chase
         */     
        virtual void chase           ( CPacman & pacman ) override;
        /**
         * @brief Sets the Ghost target coords to their scatter location, differs by the ghost type.
         */    
        virtual void scatter         ( void ) override;
    private:

};

#endif