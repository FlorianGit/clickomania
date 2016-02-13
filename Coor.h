#ifndef  __COORCLASS_INCLUDED__
#define  __COORCLASS_INCLUDED__

#include <iostream>
using namespace std;

class Coor {
public:
   Coor();
   Coor(int rowIndex, int colIndex);

   void setColIndex(int colIndex) { colIndex_ = colIndex; }
   void setRowIndex(int rowIndex) { rowIndex_ = rowIndex; }
   int getColIndex() { return colIndex_; }
   int getRowIndex() { return rowIndex_; }

   Coor getUpNb(void);
   Coor getDownNb(void);
   Coor getLeftNb(void);
   Coor getRightNb(void);
   friend ostream &operator<<(ostream &output, const Coor &coor);
   Coor operator+(const Coor& c);

private:
   int rowIndex_;
   int colIndex_;

};

#define UP    Coor(-1,0)
#define DOWN  Coor(1,0)
#define LEFT  Coor(0,-1)
#define RIGHT Coor(0,1)

#endif
