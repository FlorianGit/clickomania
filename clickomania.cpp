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

Grid readGridFromFile(string fileName)
{
   ifstream gridFile;
   int numRows, numCols, numColors;
   char temp;

   gridFile.open(fileName, ifstream::in);
   gridFile >> numRows;
   gridFile >> numCols;
   gridFile >> numColors;
   Grid grid = Grid(numRows, numCols, numColors);
   for (int rowIndex = 0; rowIndex < numRows; rowIndex++)
   {
      for(int Colindex = 0; Colindex < numCols; Colindex++)
      {
         gridFile >> temp;
         grid.setValue(Coor(rowIndex,Colindex), temp);
      }
   }
   grid.calculateGroups();
   gridFile.close();

   return grid;
}

int main (void)
{
   Coor c;

   Grid grid = readGridFromFile("ex2.grd");
   grid.calculateGroups();
   while (!grid.isFinished())
   {
      grid.calculateGroups();
      grid.printGrid();
      c = greedyFindBestMove(grid);
      grid.makeMove(c);
   }
   grid.printGrid();
   return 0;
}
