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
#include "helper.h"

using namespace std;

const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string blue("\033[1;34m");
const string magenta("\033[0;35m");
const string cyan("\033[0;36m");
const string reset("\033[0m");

char colors[7] = { 'R', 'B', 'V', 'Y', 'G', 'O', 'I' };

//---------------------------------------------------------------------
//------------------------Public functions-----------------------------
//---------------------------------------------------------------------
Grid::Grid(int numRows, int numCols, int numColors)
{
   short tmp;

   numRows_ = numRows;
   numCols_ = numCols;
   numColors_ = numColors;
   numGroups_ = 0;
   groupsUpToDate_ = false;
   grid_ = (Block**)malloc(numCols_ * sizeof(Block*));
   for (int colIndex = 0; colIndex < numCols_; colIndex++)
   {
      grid_[colIndex] = (Block*)malloc(numRows_ * sizeof(Block));
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         tmp = rand() % numColors_;
         setValue(Coor(rowIndex,colIndex), colors[tmp]);
         setVisited(Coor(rowIndex,colIndex), false);
         setGroupNumber(Coor(rowIndex,colIndex), -1);
      }
   }
   calculateGroups();
}

Grid::Grid(string fileName)
{
   ifstream gridFile;
   char temp;

   gridFile.open(fileName, ifstream::in);
   gridFile >> numRows_;
   gridFile >> numCols_;
   gridFile >> numColors_;
   numGroups_ = 0;
   groupsUpToDate_ = false;
   grid_ = (Block**)malloc(numCols_ * sizeof(Block*));
   for (int colIndex = 0; colIndex < numCols_; colIndex++)
      grid_[colIndex] = (Block*)malloc(numRows_ * sizeof(Block));

   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         gridFile >> temp;
         if (temp == '-')
            setValue(Coor(rowIndex,colIndex), ' ');
         else
            setValue(Coor(rowIndex,colIndex), temp);
      }
   }
   calculateGroups();
   gridFile.close();
}

Grid::Grid(void)
{
   char temp;

   cin >> numRows_;
   cin >> numCols_;
   cin >> numColors_;
   numGroups_ = 0;
   groupsUpToDate_ = false;
   grid_ = (Block**)malloc(numCols_ * sizeof(Block*));
   for (int colIndex = 0; colIndex < numCols_; colIndex++)
      grid_[colIndex] = (Block*)malloc(numRows_ * sizeof(Block));
   for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
   {
      for (int colIndex = 0; colIndex < numCols_; colIndex++)
      {
         cin >> temp;
         if (temp == '-')
            setValue(Coor(rowIndex,colIndex), ' ');
         else
            setValue(Coor(rowIndex,colIndex), temp);
      }
   }
   calculateGroups();
}

Grid::Grid(const Grid& grid)
{
   numRows_ = grid.getNumRows();
   numCols_ = grid.getNumCols();
   numColors_ = grid.getNumColors();
   numGroups_ = grid.getNumGroups();
   groupsUpToDate_ = grid.groupsUpToDate_;
   groups_ = grid.groups_;
   grid_ = (Block**)malloc(numCols_ * sizeof(Block*));
   for (int colIndex = 0; colIndex <numCols_; colIndex++)
   {
      grid_[colIndex] = (Block*)malloc(numRows_ * sizeof(Block));
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         setBlock(Coor(rowIndex, colIndex), EMPTY_BLOCK);
         setValue(Coor(rowIndex, colIndex), grid.getValue(Coor(rowIndex, colIndex)));
         setVisited(Coor(rowIndex, colIndex), grid.getVisited(Coor(rowIndex, colIndex)));
         setGroupNumber(Coor(rowIndex, colIndex), grid.getGroupNumber(Coor(rowIndex, colIndex)));
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

int Grid::getStackHeight(int colIndex)
{
   vector <Block> column;
   
   column = getVector(Coor(getNumRows(),colIndex), UP);
   int i = 0;
   while ( i < column.size()
        && column[i].color != ' '
         )
      i++;
   return i;
}

void Grid::printGrid(bool showColors, bool showVisited, bool showGroups) const
{
	char ch;
	
   cout << "Number of rows: " << getNumRows() << "\n";
   cout << "Number of cols: " << getNumCols() << "\n";
   cout << "Number of groups: " << getNumGroups() << "\n";
   if (showColors)
   cout << "Colors:\n";
   {
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         for (int colIndex = 0; colIndex < numCols_; colIndex++)
         {
            ch = getValue(Coor(rowIndex, colIndex));
            switch(ch)
            {
               case 'R':
                  cout << red << "R" << reset;
                  break;
               case 'B':
                  cout << blue << "B" << reset;
                  break;
               case 'V':
                  cout << cyan << "V" << reset;
                  break;
               case 'Y':
                  cout << yellow << "Y" << reset;
                  break;
               case 'G':
                  cout << green << "G" << reset;
                  break;
               case 'O':
                  cout << magenta << "O" << reset;
                  break;
               case 'I':
                  cout << "I";
                  break;
               case ' ':
                  cout << " ";
                  break;
            }
         }
         cout << "\n";
      }
   }
   if (showVisited)
   {
      cout << "Visited:\n";
      for (int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         for (int colIndex = 0; colIndex < numCols_; colIndex++)
         {
            cout << getVisited(Coor(rowIndex, colIndex));
         }
         cout << "\n";
      }
   }
   if (showGroups)
   {
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

void Grid::resetVisited(void)
{
   for(int i = 0; i < getNumRows(); i++)
      for(int j = 0; j < getNumCols(); j++)
         setVisited(Coor(i,j), false);
}

void Grid::resetGroups(void)
{
   groups_ = {};
   for(int i = 0; i < getNumRows(); i++)
      for(int j = 0; j < getNumCols(); j++)
         setGroupNumber(Coor(i,j), -1);
   numGroups_ = 0;
   groupsUpToDate_ = false;
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
   groups_.push_back(group);
   return group;
}

void Grid::calculateGroups()
{
   if(groupsUpToDate_ != true)
   {
      resetGroups();
      resetVisited();
      for( int rowIndex = 0; rowIndex < numRows_; rowIndex++)
      {
         for (int colIndex = 0; colIndex < numCols_; colIndex++)
         {
            if ( getVisited(Coor(rowIndex, colIndex)) == false
              && getValue(Coor(rowIndex, colIndex)) != ' '
               )
               calculateGroup(Coor(rowIndex, colIndex));
         }
      }
      groupsUpToDate_ = true;
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
   groupsUpToDate_ = false;
}

void Grid::collapseDown()
{
   for ( int i = 0; i < getNumCols(); i++)
   {
      setVector(Coor(getNumRows()-1,i), UP, vectorMove(getVector(Coor(getNumRows()-1,i),UP)));
   }
   groupsUpToDate_ = false;
}

bool Grid::isEmptyCol(int colIndex)
{
   bool ret = true;

   for ( int i = 0; i < getNumRows(); i++)
   {
      if (getValue(Coor(i, colIndex)) != ' ')
      {
         ret = false;
         break;
      }
   }
   return ret;
}

void Grid::emptyCol(int colIndex)
{
   for (int rowIndex = 0; rowIndex < getNumRows(); rowIndex++)
   {
      setBlock(Coor(rowIndex, colIndex), EMPTY_BLOCK);
   }
   groupsUpToDate_ = false;
}

void Grid::collapseLeft()
{
   int i = 0, j;

   while (i < getNumCols())
   {
      if (isEmptyCol(i) == true)
      {
         j = i + 1;
         while (j < getNumCols())
         {
            if (isEmptyCol(j) == true)
               j++;
            else
            {
               setVector(Coor(0, i), DOWN, getVector(Coor(0, j), DOWN));
               emptyCol(j);
               j = getNumCols();
            }
         }
      }
      i++;
   }
   groupsUpToDate_ = false;
}

void Grid::removeGroup(int groupNumber)
{
   for (int rowIndex = 0; rowIndex < getNumRows(); rowIndex++)
   {
      for (int colIndex = 0; colIndex < getNumCols(); colIndex++)
      {
         if (getGroupNumber(Coor(rowIndex,colIndex)) == groupNumber)
         {
            setBlock(Coor(rowIndex,colIndex), EMPTY_BLOCK);
         }
      }
   }
   groupsUpToDate_ = false;
}

bool Grid::hasWon(void) const
{
   bool ret = true;
   for(int rowIndex = 0; rowIndex < getNumRows(); rowIndex++)
   {
      for(int colIndex = 0; colIndex < getNumCols(); colIndex++)
      {
         if (getValue(Coor(rowIndex, colIndex))!=' ')
         {
            ret = false;
            goto exit;
         }
      }
   }
exit:
   return ret;
}

void Grid::makeMove(Coor move)
{
   if (getValue(move)==' ')
     return; 
   removeGroup(getGroupNumber(move));
   collapseDown();
   collapseLeft();
   calculateGroups();
}

vector <Coor> Grid::findPossibleMoves(void) const
{
   vector <Coor> ret = {};

   for (int i = 0; i < getNumGroups(); i++)
   {
      if (groups_[i].size > 1)
         ret.push_back(groups_[i].coors.at(0));
   }
   return ret;
}

bool Grid::isFinished(void)
{
   return (findPossibleMoves().size() == 0);
}
