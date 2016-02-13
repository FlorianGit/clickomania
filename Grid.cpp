#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>

#include "Coor.h"
#include "Grid.h"
#include "Group.h"

using namespace std;

Grid::Grid(int numRows, int numCols, int numColors)
{
   numRows_ = numRows;
   numCols_ = numCols;
   numColors_ = numColors;
   grid_ = (char**)malloc(numCols_ * sizeof(char*));
   for (int colIndex = 0; colIndex < numCols_; colIndex++)
   {
      grid_[colIndex] = (char*)malloc(numRows_ * sizeof(char));
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         grid_[colIndex][rowIndex] = '\0';
      }
   }
}

Grid::~Grid(void)
{
   for(int colIndex = 0; colIndex < numCols_; colIndex++){
      free(grid_[colIndex]);
   }
   free(grid_);
}

void Grid::printGrid(void)
{
   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         cout << grid_[colIndex][rowIndex];
      }
      cout << "\n";
   }
}

bool Grid::isValidCoor(Coor coor)
{
   int r = coor.getRowIndex(), c = coor.getColIndex();
   bool ret = false;

   if (r < 0 || c <0)
      goto exit;

   if (r >= getNumRows() || c >= getNumCols())
      goto exit;

   ret = true;
exit:
   return ret;
}


Coor Grid::findNeighbour(Coor current, Coor direction)
{
   if (isValidCoor(current + direction))
      return current + direction;
   else
      return current;
}


Group Grid::calculateGroup(Coor searchStart)
{
   stack<Coor> toBeChecked;
   Coor current, next;
   Grid visited = Grid(getNumRows(), getNumCols(), getNumColors());
   Group group;
   group.size = 1;
   group.color = getValue(searchStart);

   toBeChecked.push(searchStart);
   group.coors.push_back(searchStart);
   Coor directions[4] = {UP, DOWN, LEFT, RIGHT};
   while(!toBeChecked.empty())
   {
      current = toBeChecked.top();
      toBeChecked.pop();
      visited.setValue(current, 'y');
      for (int dirIndex = 0; dirIndex < 4; dirIndex++)
      {
         next = findNeighbour(current, directions[dirIndex]);
         if (getValue(next) == group.color
            && visited.getValue(next) != 'y')
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            visited.setValue(next, 'y');
            group.size++;
         }
      }
   }
   return group;
}
