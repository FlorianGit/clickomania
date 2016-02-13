#ifndef  __COORCLASS_INCLUDED__
#define  __COORCLASS_INCLUDED__

#include <iostream>
using namespace std;

class Coor {
private:
   int row_index;
   int col_index;

public:
   Coor();
   Coor(int r_index, int c_index);

   void setColIndex(int c_index) { col_index = c_index; }
   void setRowIndex(int r_index) { row_index = r_index; }
   int getColIndex() { return col_index; }
   int getRowIndex() { return row_index; }

   Coor getUpNb(void);
   Coor getDownNb(void);
   Coor getLeftNb(void);
   Coor getRightNb(void);
   friend ostream &operator<<(ostream &output, const Coor &coor);
};

#endif
