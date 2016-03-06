#include "testSolver.h"
#include "findMove.h"
#include "Grid.h"
#include "Coor.h"

void testSolver(void)
{
   Coor c;
   int numMoves, numGroupsLeft, totalMoves;
   for (int searchDepth = 1; searchDepth < 4; searchDepth++)
   {
      for (int strategy = 0; strategy < FINDMOVE_NUM_STRATEGIES; strategy++)
      {
         setStrategy(strategy);
         numGroupsLeft = 0;
         totalMoves = 0;
         for (int i = 0; i < 100; i++)
         {
            Grid grid(10,10,2);
            while (!grid.isFinished())
            {
               numMoves = grid.findPossibleMoves().size();
               if (numMoves < 10)
                  c = findBestMoveWithSearchDepth(grid, searchDepth);
               else 
                  c = findBestMoveWithSearchDepth(grid, 1);
               
               grid.makeMove(c);
               totalMoves++;
               grid.calculateGroups();
            }
            numGroupsLeft += grid.getNumGroups();
         }
         printf("Strategynumber %d totalgroupsleft %d totalmovesmade: %d\n", strategy, numGroupsLeft, totalMoves);
      }
   }
} 
