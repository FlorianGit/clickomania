#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <iomanip>

#include "Coor.h"
#include "Grid.h"
#include "Group.h"

using namespace std;

Grid::Grid(int numRows, int numCols, int numColors)
{
   numRows_ = numRows;
   numCols_ = numCols;
   numColors_ = numColors;
   numGroups_ = 0;
   grid_ = (Block**)malloc(numCols_ * sizeof(Block*));
   for (int colIndex = 0; colIndex < numCols_; colIndex++)
   {
      grid_[colIndex] = (Block*)malloc(numRows_ * sizeof(Block));
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         setValue(Coor(rowIndex,colIndex), '\0');
         setVisited(Coor(rowIndex,colIndex), false);
         setGroupNumber(Coor(rowIndex,colIndex), -1);
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
   cout << "Number of rows: " << getNumRows() << "\n";
   cout << "Number of cols: " << getNumCols() << "\n";
   cout << "Number of groups: " << getNumGroups() << "\n";
   cout << "Colors:\n";
   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         cout << getValue(Coor(rowIndex, colIndex));
      }
      cout << "\n";
   }
   cout << "Visited:\n";
   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         cout << getVisited(Coor(rowIndex, colIndex));
      }
      cout << "\n";
   }
   cout << "Group Numbers:\n";
   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         cout << setw(3) << getGroupNumber(Coor(rowIndex, colIndex));
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
   Group group;
   group.size = 1;
   group.color = getValue(searchStart);
   group.number = getNumGroups();
   numGroups_++;
   toBeChecked.push(searchStart);
   group.coors.push_back(searchStart);
   setGroupNumber(searchStart, group.number);
   Coor directions[4] = {UP, DOWN, LEFT, RIGHT};
   while(!toBeChecked.empty())
   {
      current = toBeChecked.top();
      toBeChecked.pop();
      setVisited(current, true);
      for (int dirIndex = 0; dirIndex < 4; dirIndex++)
      {
         next = findNeighbour(current, directions[dirIndex]);
         if (getValue(next) == group.color
            && getVisited(next) != true)
         {
            toBeChecked.push(next);
            group.coors.push_back(next);
            setGroupNumber(next, group.number);
            setVisited(next, true);
            group.size++;
         }
      }
   }
   return group;
}

void Grid::calculateGroups()
{
   for( int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         if (getVisited(Coor(rowIndex, colIndex)) == false)
            calculateGroup(Coor(rowIndex, colIndex));
      }
   }
}

vector <Block> Grid::getVector(Coor start, Coor direction)
{
   vector <Block> ret = {};

   while( isValidCoor(start) )
   {
      ret.push_back(getBlock(start));
      start = start + direction;
   }
   return ret;
}

void Grid::setVector(Coor start, Coor direction, vector <Block> vec)
{
   for (int i = 0; i < vec.size(); i++)
   {
      setBlock(start, vec[i]);
      start = start + direction;
   }
}
