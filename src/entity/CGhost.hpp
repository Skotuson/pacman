#ifndef CGHOST_H
#define CGHOST_H

#include "CEntity.hpp"
#include "CPacman.hpp"

const size_t GHOST_OFFSET = 10;

enum GhostStrategy { CLASSIC = 0, RABID = 1 };

/**
 @brief Represents the enemy, which player has to avoid and outsmart
*/
class CGhost : public CEntity {
    public:
                    /**
                     * @param[in] x Origin X coord
                     * @param[in] y Origin Y coord
                     * @param[in] look Entity character representation
                     * @param[in] color ANSI sequence which colors terminal
                     */
                     CGhost          ( size_t x, 
                                       size_t y, 
                                       char look, 
                                       std::string color );

        /**
         * @brief Sets the Ghost target coords relative to pacman, according to the ghost type.
         * @param[in] pacman Pacman to chase
         */        
        virtual void chase           ( CPacman & pacman ) = 0;
        /**
         * @brief Sets the Ghost target coords to pacman's position.
         * @param[in] pacman Pacman to chase
         */        
                void rabidChase      ( CPacman & pacman );
        /**
         * @brief Sets the Ghost target coords to their scatter location, differs by the ghost type.
         */        
        virtual void scatter         ( void ) = 0;

        /**
         * @brief Checks if an entity is Pacman
         * @return True if entity is Pacman, false otherwise
         */
        virtual bool isPacman        ( void ) override;
                
        /**
         * @brief Sets the ghost coordinates away from Pacman.
         * @param[in] pacman Pacman to get away from
         */        
        void frighten        ( CPacman & pacman );
        /**
         * @brief Kills the ghost, removing him from the maze and setting up his respawn timer.
         */  
        void kill            ( void );
        /**
         * @brief Attempts to revive a ghost by checking state of his death timer.
         * If ghost still has some time on his death timer, decremenets the death timer.
         */  
        void attemptRespawn  ( void );
        /**
         * @brief Function checks if the ghost is dead.
         */  
        bool isDead          ( void );

        int  getTargetX      ( void );
        int  getTargetY      ( void );
        
        static GhostStrategy ghostStrategy;
        static size_t        ghostMaxScatterX,
                             ghostMaxScatterY,
                             ghostDeathTimer;
    protected:
        bool   m_IsDead   = false;
        size_t deathTimer = 0;

        int    m_TargetX = 0, 
               m_TargetY = 0;

};

#endif