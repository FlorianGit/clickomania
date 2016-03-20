#ifndef __GRIDCLASS_INCLUDED__
#define __GRIDCLASS_INCLUDED__

#include "Coor.h"
#include "Group.h"

class Grid {
public:
   //Constructors
   Grid(int numRows, int numCols, int numColors);
   Grid(string fileName);
   Grid(void);
   Grid(const Grid& grid);
   ~Grid(void);

   //get and set functions
   void setValue(Coor c, char value) { valueGrid_[c.getColIndex() + numCols_ * c.getRowIndex()] = value; }
   char getValue(Coor c) const { return valueGrid_[c.getColIndex() + numCols_ * c.getRowIndex()]; }
   void setVisited(Coor c, bool visited) { visitedGrid_[c.getColIndex() + numCols_ * c.getRowIndex()] = visited; }
   bool getVisited(Coor c) const { return visitedGrid_[c.getColIndex() + numCols_ * c.getRowIndex()]; }
   void setGroupNumber(Coor c, int group) { groupNumberGrid_[c.getColIndex() + numCols_ * c.getRowIndex()] = group; }
   int getGroupNumber(Coor c) const { return groupNumberGrid_[c.getColIndex() + numCols_ * c.getRowIndex()]; }
   int getNumRows(void) const { return numRows_; }
   int getNumCols(void) const { return numCols_; }
   int getNumColors(void) const { return numColors_; }
   int getNumGroups(void) const { return numGroups_; }
   int getGroupSize(int groupNumber) const { return groups_[groupNumber].size; }

   //other functions
   void printGrid(bool showColors, bool showVisited, bool showGroups) const ;
   void calculateGroups();
   void makeMove(Coor move);
   vector <Coor> findPossibleMoves(void) const;
   Group calculateGroup(Coor start_search);
   bool hasWon(void) const;
   bool isFinished(void);
   int getStackHeight(int colIndex);

private:
   int numRows_;
   int numCols_;
   int numColors_;
   char *valueGrid_;
   bool *visitedGrid_;
   int *groupNumberGrid_;
   int numGroups_;
   vector <Group> groups_;
   bool groupsUpToDate_;

   bool isValidCoor(Coor coor);
   Coor findNeighbour(Coor current, Coor direction);
   void resetVisited(void);
   void resetGroups(void);
   void collapseDown();
   bool isEmptyCol(int colIndex);
   void emptyCol(int colIndex);
   void collapseLeft();
   void removeGroup(int groupNumber);
};



#endif
