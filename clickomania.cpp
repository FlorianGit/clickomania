#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

#include "Coor.h"
#include "Grid.h"

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

   gridFile.close();

   return grid;
}

int main (void)
{
   Grid grid = readGridFromFile("ex1.grd");
   grid.calculateGroups();
   grid.printGrid();
   return 0;
}
