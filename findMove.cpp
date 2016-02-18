
#include "Grid.h"

int calculateScore(Grid grid)
{
   grid.calculateGroups();
   return grid.getNumGroups();
}

Coor greedyFindBestMove(Grid grid)
{
   vector <Coor> moves;
   int i, numMoves, minScore, tmpScore, minMoveIndex;
   Grid temp = Grid(grid.getNumRows(), grid.getNumCols(), grid.getNumColors());
   Coor minMove;

   moves = grid.findPossibleMoves();
   numMoves = moves.size();
   for ( i = 0; i < numMoves; i++)
   {
      temp = grid;
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
