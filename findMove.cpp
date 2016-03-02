
#include <stdio.h>

#include "Grid.h"

int calculateScore(Grid grid)
{
   //return grid.findPossibleMoves().size();
   return grid.getNumGroups();
}

Coor greedyFindBestMove(const Grid& grid)
{
   vector <Coor> moves;
   int i, numMoves, minScore, tmpScore, minMoveIndex;
   Coor minMove;

   moves = grid.findPossibleMoves();
   numMoves = moves.size();
   moves[0];
   moves[1];
   for ( i = 0; i < numMoves; i++)
   {
      Grid temp = grid;
      temp.makeMove(moves[i]);
      tmpScore = calculateScore(temp);
      if (minScore < tmpScore)
      {
         minScore = tmpScore;
         minMoveIndex = i;
      }
   }
   return moves[minMoveIndex];
}
