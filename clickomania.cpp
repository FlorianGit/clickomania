#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>

#include "Coor.h"
#include "Grid.h"
#include "findMove.h"
#include "testSolver.h"

using namespace std;

void readCommandFromInput(Grid grid)
{
   bool exit = false;
   char tmp[25];
   int x,y; 
   
   while (!exit)
   {
      scanf("%s", tmp);
      if (strcmp("exit",tmp)==0)
         exit = true;
      if (strcmp("printGrid",tmp)==0)
         grid.printGrid(true,false,true);
      if (strcmp(tmp, "calculateGroups")==0)
         grid.calculateGroups();
      if (strcmp(tmp, "makeMove")==0)
      {
         scanf("%d %d", &x, &y);
         grid.makeMove(Coor(x,y));
      }
          
   }
}
int main (void)
{
   srand(time(NULL));
   testSolver();
   /*Coor c;
   Grid grid(20,10,5);
   
   while (!grid.isFinished())
   {
      grid.printGrid(true, false, false);
      int numMoves = grid.findPossibleMoves().size();
      if (numMoves < 10)
         c = findBestMoveWithSearchDepth(grid, 3);
      else if (numMoves < 30)
         c = findBestMoveWithSearchDepth(grid, 1);
      else 
         c = findBestMoveWithSearchDepth(grid, 1);
      
      grid.makeMove(c);
      grid.calculateGroups();
   }
   grid.printGrid(true, false, false);*/
   return 0;
}
