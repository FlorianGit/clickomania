#include "Coor.h"
#include <iostream>

using namespace std;

Coor::Coor()
{
   rowIndex_ = 0;
   colIndex_ = 0;
}

Coor Coor::operator+(const Coor& c)
{
   Coor ret = Coor(this->rowIndex_ + c.rowIndex_, this->colIndex_ + c.colIndex_);
   return ret;
}

Coor::Coor(int rowIndex, int colIndex)
{
   rowIndex_ = rowIndex;
   colIndex_ = colIndex;
}

Coor Coor::getUpNb(void)
{
   Coor nb = Coor(rowIndex_ -1, colIndex_);
   return nb;
};

Coor Coor::getDownNb(void)
{
   Coor nb = Coor(rowIndex_ + 1, colIndex_);
   return nb;
};

Coor Coor::getLeftNb(void)
{
   Coor nb = Coor(rowIndex_, colIndex_ - 1);
   return nb;
};

Coor Coor::getRightNb(void)
{
   Coor nb = Coor(rowIndex_, colIndex_ + 1);
   return nb;
};

ostream &operator<<(ostream &output, const Coor &coor)
{
   output << coor.rowIndex_ << " " << coor.colIndex_ << "\n";
   return output;
}
