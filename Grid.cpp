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

Group Grid::calculateGroup(Coor searchStart)
{
   stack<Coor> toBeChecked;
   Coor current, next;
   Grid visited = Grid(getNumRows(), getNumCols(), getNumColors());
   Group group;
   group.size = 1;
   group.color = getGridValue(searchStart);

   toBeChecked.push(searchStart);
   group.coors.push_back(searchStart);

   while(!toBeChecked.empty())
   {
      current = toBeChecked.top();
      toBeChecked.pop();
      visited.setGridValue(current, 'y');
      if (current.getRowIndex() > 0)
      {
         next = current.getUpNb();
         if (getGridValue(next) == group.color
            && visited.getGridValue(next) != 'y')
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            visited.setGridValue(next, 'y');
            group.size++;
         }
      }

      if (current.getRowIndex() < getNumRows() -1)
      {
         next = current.getDownNb();
         if (getGridValue(next) == group.color
            && visited.getGridValue(next) != 'y')
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            visited.setGridValue(next, 'y');
            group.size++;
         }
      }

      if (current.getColIndex() > 0 )
      {
         next = current.getLeftNb();
         if (getGridValue(next) == group.color
            && visited.getGridValue(next) != 'y')
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            visited.setGridValue(next, 'y');
            group.size++;
         }
      }

      if (current.getColIndex() < getNumCols() -1)
      {
         next = current.getRightNb();
         if (getGridValue(next) == group.color
            && visited.getGridValue(next) != 'y')
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            visited.setGridValue(next, 'y');
            group.size++;
         }
      }
   }
   return group;
}
