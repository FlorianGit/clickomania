#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include "coorclass.h"
#include "gridclass.h"

using namespace std;

Gridclass readGridFromFile(string file_name)
{
   ifstream gridfile;
   int x,y,k;
   Coor c;
   char temp;

   gridfile.open(file_name, ifstream::in);
   gridfile >> x;
   gridfile >> y;
   gridfile >> k;
   Gridclass grid = Gridclass(x, y, k);
   for (int row_index = 0; row_index < x; row_index++)
   {
      for(int col_index = 0; col_index < y; col_index++)
      {
         gridfile >> temp;
         c.setRowIndex(row_index);
         c.setColIndex(col_index);
         grid.setGridValue(c, temp);
      }
   }

   gridfile.close();

   return grid;
}

int main (void)
{
   Gridclass grid = readGridFromFile("ex1.grd");
   grid.printGrid();
   printf("test2");
   return 0;
}
