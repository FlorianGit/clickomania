#ifndef __FINDMOVE_H_INCLUDED__
#define __FINDMOVE_H_INCLUDED__

#include "Grid.h"

#define FINDMOVE_NUM_STRATEGIES         4

#define MINIMIZE_NUM_POSSIBLE_MOVES     0
#define MINIMIZE_NUM_GROUPS             1
#define MINIMIZE_AVG_GROUP_SIZE         2
#define MINIMIZE_NUM_SINGLETONS         3

extern void setStrategy(int strategy);
extern Coor findBestMoveWithSearchDepth(const Grid& grid, int searchDepth);
#endif
