#ifndef CENTITY_H
#define CENTITY_H

#include "../game/CGeometry.hpp"
#include <ostream>
#include <string>

/**
 * @brief Represents a moving entity, serves as a base class for ghosts and Pacman.
 */
class CEntity {
    public:
                /**
                 * @param[in] x Origin X coord
                 * @param[in] y Origin Y coord
                 * @param[in] look Entity character representation
                 * @param[in] color ANSI sequence which colors terminal
                 */
                CEntity            ( size_t      x, 
                                     size_t      y, 
                                     char        look, 
                                     std::string color );
        virtual ~CEntity           ( void ) = default;

        
        /**
         * @brief Checks if an entity is Pacman
         * @return True if entity is Pacman, false otherwise
         */
        virtual bool isPacman      ( void ) = 0;

        /**
         * @brief Sets direction based on last keyboard input
         * @param[in] keyboardInput Last keyboard input
         */
        void      setDirection  ( char keyboardInput );
        /**
         * @brief Sets direction based on a direction
         * @param[in] dir Direction to set
         */
        void      setDirection  ( Direction dir );
        /**
         * @brief Direction getter
         */
        Direction getDirection  ( void );

        /**
         * @brief Checks if the entity is at the current (x,y) coords
         * @param[in] x X coords to check
         * @param[in] y Y coords to check
         * @return true if entity is at (x,y) coords, false otherwise
         */
        bool   isAt             ( size_t x, size_t y );
        /**
         * @brief Moves the entity in set direction
         */
        void   move             ( void );

        void   setX             ( size_t x );
        void   setY             ( size_t y );
        size_t getX             ( void );
        size_t getY             ( void );

        friend std::ostream & operator << ( std::ostream & os, const CEntity & entity );

    protected:
        size_t    m_X, 
                  m_Y,
                  m_OriginX, 
                  m_OriginY;

        Direction m_Direction = STATIONARY;
        char   m_Look;
        std::string m_ANSI_color;
        std::string m_ANSI_origColor;
};

#endif