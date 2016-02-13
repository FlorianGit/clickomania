#include "Coor.h"
#include <iostream>

using namespace std;

Coor::Coor()
{
   row_index = 0;
   col_index = 0;
}

Coor::Coor(int r_index, int c_index)
{
   row_index = r_index;
   col_index = c_index;
}

Coor Coor::getUpNb(void)
{
   Coor nb = Coor(row_index -1, col_index);
   return nb;
};

Coor Coor::getDownNb(void)
{
   Coor nb = Coor(row_index + 1, col_index);
   return nb;
};

Coor Coor::getLeftNb(void)
{
   Coor nb = Coor(row_index, col_index - 1);
   return nb;
};

Coor Coor::getRightNb(void)
{
   Coor nb = Coor(row_index, col_index + 1);
   return nb;
};

ostream &operator<<(ostream &output, const Coor &coor)
{
   output << coor.row_index << " " << coor.col_index << "\n";
   return output;
}
