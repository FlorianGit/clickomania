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

private:
   int rowIndex_;
   int colIndex_;

};

#endif
