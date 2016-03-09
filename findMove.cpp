
#include <stdio.h>
#include <limits.h>

#include "findMove.h"
#include "Grid.h"

//------------------------------------------------------------------------
//-----------------Private Declarations-----------------------------------
//------------------------------------------------------------------------

float (*calculateScoreFunc)(Grid grid) = NULL;

float calculateNumPossibleMoves(Grid grid);
float calculateNumGroups(Grid grid);
float calculateAverageGroupSize(Grid grid);
float calculateNumSingletons(Grid grid);
float calculateMaxDiffBetweenStacks(Grid grid);

//------------------------------------------------------------------------
//-----------------Public definitions-------------------------------------
//------------------------------------------------------------------------

extern void setStrategy(int strategy)
{
   switch (strategy)
   {
      case MINIMIZE_NUM_POSSIBLE_MOVES:
         calculateScoreFunc = calculateNumPossibleMoves;
         break;
      case MINIMIZE_NUM_GROUPS:
         calculateScoreFunc = calculateNumGroups;
         break;
      case MINIMIZE_AVG_GROUP_SIZE:
         calculateScoreFunc = calculateAverageGroupSize;
         break;
      case MINIMIZE_NUM_SINGLETONS:
         calculateScoreFunc = calculateNumSingletons;
         break;
      case MINIMIZE_MAX_STACK_HEIGHT_DIFF:
         calculateScoreFunc = calculateMaxDiffBetweenStacks;
      default:
         calculateScoreFunc = calculateAverageGroupSize;
   }
}   

extern Coor findBestMoveWithSearchDepth(const Grid& grid, int searchDepth)
{
   vector <Coor> moves;
   int i, numMoves, minMoveIndex;
   float minScore = INT_MAX, tmpScore;
   Coor minMove;

   if (calculateScoreFunc == NULL)
      setStrategy(3);

   moves = grid.findPossibleMoves();
   numMoves = moves.size();
   if (numMoves == 0)
      return Coor(0,0);
   minMoveIndex = 0;
   for ( i = 0; i < numMoves; i++)
   {
      Grid temp = grid;
      temp.makeMove(moves[i]);
      if (searchDepth > 1)
         temp.makeMove(findBestMoveWithSearchDepth(temp, searchDepth -1));
      tmpScore = calculateScoreFunc(temp);
      if (tmpScore < minScore)
      {
         minScore = tmpScore;
         minMoveIndex = i;
      }
   }
   return moves[minMoveIndex];
}

//------------------------------------------------------------------------
//-----------------Private functions--------------------------------------
//------------------------------------------------------------------------

float calculateNumPossibleMoves(Grid grid)
{
   return grid.findPossibleMoves().size();
}

float calculateNumGroups(Grid grid)
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

float calculateNumSingletons(Grid grid)
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
 
float calculateMaxDiffBetweenStacks(Grid grid)
{
   int maxDiff = 0, prevHeight, currHeight;
   prevHeight = grid.getStackHeight(0); 
   for (int i = 1; i < grid.getNumCols(); i++)
   {
      currHeight = grid.getStackHeight(1);
      if (abs(currHeight - prevHeight) > maxDiff)
         maxDiff = abs(currHeight - prevHeight);
      prevHeight = currHeight;
   }
   return (float)maxDiff;
}
