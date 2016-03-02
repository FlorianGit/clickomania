#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "Coor.h"
#include "Grid.h"
#include "helper.h"
#include "findMove.h"

using namespace std;

int main (void)
{
   Coor c;

   Grid grid(20,20,5);
   grid.calculateGroups();
   while (!grid.isFinished())
   {
      grid.printGrid(true, false, true);
      c = greedyFindBestMove(grid);
      grid.makeMove(c);
      grid.calculateGroups();
   }
   grid.printGrid(true, false, true);
   return 0;
}
