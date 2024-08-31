#ifndef CCONFIG_H
#define CCONFIG_H

#include <string>
#include <fstream>
#include "../maze/CMaze.hpp"
#include "../maze/CTeleportTile.hpp"
#include "../entity/CPacman.hpp"
#include "../entity/CGhost.hpp"

const size_t MAX_DIM = 50;
const size_t MAX_TIMER = 250;

/**
 * @brief Class which takes care of handling settings from files.
 */
class CConfig {
    public:
        /**
         * @brief Open file and provide the input stream from it.
         * @param[in] filename Filename
         * @param[out] ifs Readable stream from the file 
         */
        bool openFile ( std::string filename, std::ifstream & ifs );
        /** 
         * @brief Parses game configuration from a text file, checks
         * if the input is valid and instantiates the CMaze object.
         * @param[in] filename File which contains the game configuration.
         * @param[out] maze   Maze pointer into which the maze from file will be loaded.
         * @param[out] pacman Pacman instance which will be associated with loaded game configuration.
         * @param[out] ghosts Ghost instances which will be associated with loaded game configuration.
         * @param[out] coins  Output parameter which counts the number of coins present in loaded game configuration.
         * @return True if no error in loading the game has occured, false otherwise.
         */
        bool loadGame   ( std::ifstream & ifs,
                             CMaze   *& maze,  
                             CPacman *  pacman,
                             std::vector<CGhost*> * ghosts, 
                             size_t & coins );
        
        /** 
         * @brief Print current error message
         * @param[out] os Stream to print the message to
         */
        void      printErr                  ( std::ostream & os );
        
        size_t getScatterTimer    ( void );
        size_t getChaseTimer      ( void );
        size_t getFrightenedTimer ( void );

        private:
                /**
         * @brief Determines which type of maze tile to add into the maze.
         * Teleport tile is handled separately due to its different nature.
         * @param[out] m Maze to insert the tiles in
         * @param[in] c Tile info from the maze file
         * @param[in] x X coord of the tile
         * @param[in] y Y coord of the tile
         * @param[out] coins Total coin count
         */
        void    addTile    ( CMaze & m, 
                             char c, 
                             size_t x, 
                             size_t y, 
                             size_t & coins );
        /**
         * @brief Handles adding Teleport Tile into the maze.
         * @param[out] m Maze to insert the teleport tile in
         * @param[in] x X coord of the teleport tile
         * @param[in] y Y coord of the teleport tile
         * @param[out] t1 First teleport entrance/exit
         * @param[out] t2 Second teleport entrance/exit
         * @return True if TTile was added sucessfully, false otherwise.
         */
        bool    addTTile   ( CMaze & m, 
                             size_t x, 
                             size_t y, 
                             CTeleportTile *& t1,
                             CTeleportTile *& t2 );
        
        /**
         * @brief Handles adding Ghosts to their respective container
         * @param[out] g Container to insert ghosts in
         * @param[in] c Ghost info from the maze file
         * @param[in] x X coord of the ghost
         * @param[in] y Y coord of the ghost
         */
        void    addGhost   ( std::vector<CGhost*> & g, 
                             char c, 
                             size_t x, 
                             size_t y );
        
        /** 
         * @brief Determines what direction the teleport is heading based on its coords.
         * @param[in] x X Coord
         * @param[in] y Y Coord
         * @return Direction in which the teleport is heading
         */
        Direction determineTeleportEntryDir ( size_t x, size_t y );
        
        /** 
         * @brief Checks if the cols read from the file are valid.
         * @return true if all file params are in valid range, false otherwise.
         */
        bool      validFileParams           ( void );    
        /** 
         * @brief Checks if the cols read from the file are valid.
         * @param[in] cols Currently read cols
         * @return true if number of cols read from the file is valid, false otherwise.
         */
        bool      validCols                 ( size_t cols );    
       
        /** 
         * @brief Checks if the rows read are less or equal than expected.
         * @param[in] rows Currently read rows
         * @return true if number of rows read from the file is valid, false otherwise.
         */
        bool      validRows                 ( size_t rows );    
       
        /** 
         * @brief Set error message
         * @param[in] err Error message
         */
        void      setErr                    ( const std::string & err );
    
        std::string m_Err;
        size_t m_MazeRows, 
               m_MazeCols,
               m_ScatterTimer,
               m_ChaseTimer,
               m_FrightenedTimer,
               m_GameMode;
};

#endif