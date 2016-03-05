#ifndef __FINDMOVE_H_INCLUDED__
#define __FINDMOVE_H_INCLUDED__

#include "Grid.h"

int calculateScore(Grid grid);
Coor greedyFindBestMove(const Grid& grid);
Coor findBestMoveWithSearchDepth(const Grid& grid, int searchDepth);
#endif
