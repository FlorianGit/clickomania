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

   Grid grid("ex1.grd");
   while (!grid.isFinished())
   {
      grid.calculateGroups();
      grid.printGrid(true, false, false);
      c = greedyFindBestMove(grid);
      grid.makeMove(c);
   }
   grid.printGrid(true, false, false);
   return 0;
}
