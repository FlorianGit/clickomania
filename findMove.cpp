
#include <stdio.h>
#include <limits.h>

#include "Grid.h"

int calculateNumPossibleMoves(Grid grid)
{
   return grid.findPossibleMoves().size();
}

int calculateNumGroups(Grid grid)
{
   return grid.getNumGroups();
}

float calculateAverageGroupSize(Grid grid)
{
   int totalSize = 0;
   int numGroups = grid.getNumGroups();

   for(int i = 0; i < numGroups; i++)
   {
      totalSize += grid.getGroupSize(i);
   }
   return -(float)totalSize/(float)numGroups;
}

int calculateNumSingletons(Grid grid)
{
   int numSingletons = 0;
   int numGroups = grid.getNumGroups();

   for(int i = 0; i < numGroups; i++)
   {
      if (grid.getGroupSize(i)==1)
         numSingletons += 1;
   }
   return numSingletons;
}
   
Coor greedyFindBestMove(const Grid& grid)
{
   vector <Coor> moves;
   int i, numMoves, minMoveIndex;
   float minScore = INT_MAX, tmpScore;
   Coor minMove;

   moves = grid.findPossibleMoves();
   numMoves = moves.size();
   for ( i = 0; i < numMoves; i++)
   {
      Grid temp = grid;
      temp.makeMove(moves[i]);
      //tmpScore = calculateNumPossibleMoves(temp);
      //tmpScore = calculateNumGroups(temp);
      tmpScore = calculateAverageGroupSize(temp);
      //tmpScore = calculateNumSingletons(temp);
      if (tmpScore < minScore)
      {
         minScore = tmpScore;
         minMoveIndex = i;
      }
   }
   return moves[minMoveIndex];
}

Coor findBestMoveWithSearchDepth(const Grid& grid, int searchDepth)
{
   vector <Coor> moves;
   int i, numMoves, minMoveIndex;
   float minScore = INT_MAX, tmpScore;
   Coor minMove;

   moves = grid.findPossibleMoves();
   numMoves = moves.size();
   if (numMoves == 0)
      return Coor(0,0);
   for ( i = 0; i < numMoves; i++)
   {
      Grid temp = grid;
      temp.makeMove(moves[i]);
      if (searchDepth > 1)
         temp.makeMove(findBestMoveWithSearchDepth(temp, searchDepth -1));
      //tmpScore = calculateNumPossibleMoves(temp);
      //tmpScore = calculateNumGroups(temp);
      tmpScore = calculateAverageGroupSize(temp);
      //tmpScore = calculateNumSingletons(temp);
      if (tmpScore < minScore)
      {
         minScore = tmpScore;
         minMoveIndex = i;
      }
   }
   return moves[minMoveIndex];
}

