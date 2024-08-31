#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdlib>

const size_t NO_DIRECTIONS = 5;
/**
 * @brief Enum which represent directions in which entities can move.
 */
enum Direction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, STATIONARY = 4 };

#endif