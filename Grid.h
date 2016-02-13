#ifndef __GRIDCLASS_INCLUDED__
#define __GRIDCLASS_INCLUDED__

#include "Coor.h"
#include "Group.h"

class Grid {
public:
   //Constructors
   Grid(int numRows, int numCols, int numColors);
   ~Grid(void);

   //get and set functions
   void setGridValue(Coor c, char value) { grid_[c.getColIndex()][c.getRowIndex()] = value; }
   int getGridValue(Coor c) { return grid_[c.getColIndex()][c.getRowIndex()]; }
   int getNumRows(void) { return numRows_; }
   int getNumCols(void) { return numCols_; }
   int getNumColors(void) { return numColors_; }

   //other functions
   void printGrid(void);
   bool isValidCoor(Coor coor);
   Coor findNeighbour(Coor current, Coor direction);
   Group calculateGroup(Coor start_search);

private:
   int numRows_;
   int numCols_;
   int numColors_;
   char** grid_;

};



#endif
