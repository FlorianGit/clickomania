#ifndef __GRIDCLASS_INCLUDED__
#define __GRIDCLASS_INCLUDED__

#include "Coor.h"
#include "Group.h"
#include "Block.h"

class Grid {
public:
   //Constructors
   Grid(int numRows, int numCols, int numColors);
   ~Grid(void);

   //get and set functions
   void setValue(Coor c, char value) { grid_[c.getColIndex()][c.getRowIndex()].color = value; }
   char getValue(Coor c) { return grid_[c.getColIndex()][c.getRowIndex()].color; }
   void setVisited(Coor c, bool visited) { grid_[c.getColIndex()][c.getRowIndex()].visited = visited; }
   bool getVisited(Coor c) { return grid_[c.getColIndex()][c.getRowIndex()].visited; }
   void setGroupNumber(Coor c, int group) { grid_[c.getColIndex()][c.getRowIndex()].groupNumber = group; }
   int getGroupNumber(Coor c) { return grid_[c.getColIndex()][c.getRowIndex()].groupNumber; }
   void setBlock(Coor c, Block b) { grid_[c.getColIndex()][c.getRowIndex()] = b; }
   Block getBlock(Coor c) { return grid_[c.getColIndex()][c.getRowIndex()]; }
   int getNumRows(void) { return numRows_; }
   int getNumCols(void) { return numCols_; }
   int getNumColors(void) { return numColors_; }
   int getNumGroups(void) { return numGroups_; }
   //other functions
   void printGrid(void);
   bool isValidCoor(Coor coor);
   Coor findNeighbour(Coor current, Coor direction);
   Group calculateGroup(Coor start_search);
   void calculateGroups();
   vector <Block> getVector(Coor start, Coor direction);
   void setVector(Coor start, Coor direction, vector <Block> vec);
   void collapseDown();
   void removeGroup(int groupNumber);

private:
   int numRows_;
   int numCols_;
   int numColors_;
   Block** grid_;
   int numGroups_;
};



#endif
