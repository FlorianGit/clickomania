#include <fstream>
#include <time.h>

#include "testSolver.h"
#include "findMove.h"
#include "Grid.h"
#include "Coor.h"

static ofstream logFile;

static bool openLogFile(void);
static bool closeLogFile(void);
static void writeOutput(int strategy, int searchDepth, int numGroupsLeft, int movesMade, double elapsedTime);

void testSolver(void)
{
   Coor c;
   int numMoves, numGroupsLeft, totalMoves;
   clock_t begin, end;

   openLogFile();

   for (int searchDepth = 1; searchDepth <= 2; searchDepth++)
   {
      for (int strategy = 0; strategy < FINDMOVE_NUM_STRATEGIES; strategy++)
      {
         setStrategy(strategy);
         for (int i = 0; i < 30; i++)
         {
            begin = clock();
            totalMoves = 0;
            Grid grid(20,10,5);
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
            numGroupsLeft = grid.getNumGroups();
            end = clock();
            writeOutput(strategy, searchDepth, numGroupsLeft, totalMoves, (double)(end-begin)/CLOCKS_PER_SEC);
         }
      }
   }
   closeLogFile();
}

static bool openLogFile(void)
{
   logFile.open("click.csv",ofstream::out);
   logFile << "strategy" << "," << "searchDepth" << "," << "numGroupsleft" << "," << "movesMade" << "," << "elapsedTime" << "\n";

   return true;
}

static bool closeLogFile(void)
{
   logFile.close();
}

static void writeOutput(int strategy, int searchDepth, int numGroupsLeft, int movesMade, double elapsedTime)
{
   logFile << strategy << "," << searchDepth << "," << numGroupsLeft << "," << movesMade << "," << elapsedTime << "\n";
}
