#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

class Coor {
   int row_index;
   int col_index;

public:
   Coor()
   {
      row_index = 0;
      col_index = 0;
   }

   Coor(int r_index, int c_index)
   {
      row_index = r_index;
      col_index = c_index;
   }

   void setColIndex(int c_index)
   {
      col_index = c_index;
   }

   void setRowIndex(int r_index)
   {
      row_index = r_index;
   }

   int getColIndex()
   {
      return col_index;
   }

   int getRowIndex()
   {
      return row_index;
   }

   Coor getUpNb(void)
   {
      Coor nb = Coor(row_index -1, col_index);
      return nb;
   };

   Coor getDownNb(void)
   {
      Coor nb = Coor(row_index + 1, col_index);
      return nb;
   };

   Coor getLeftNb(void)
   {
      Coor nb = Coor(row_index, col_index - 1);
      return nb;
   };

   Coor getRightNb(void)
   {
      Coor nb = Coor(row_index, col_index + 1);
      return nb;
   };
};

class Gridclass {
   int num_rows;
   int num_cols;
   int num_colors;
   char** grid;

   public:
   Gridclass(int num_r, int num_c, int num_clrs)
   {
      num_rows = num_r;
      num_cols = num_c;
      num_colors = num_clrs;
      grid = (char**)malloc(num_cols * sizeof(char*));
      for (int col_index = 0; col_index < num_cols; col_index++)
      {
         grid[col_index] = (char*)malloc(num_rows * sizeof(char));
         for (int row_index = 0; row_index < num_rows; row_index++)
         {
            grid[col_index][row_index] = '\0';
         }
      }
   }

   ~Gridclass(void)
   {
      for(int col_index = 0; col_index < num_cols; col_index++){
         free(grid[col_index]);
      }
      free(grid);
   }
   void setGridValue(Coor c, char value)
   {
      grid[c.getColIndex()][c.getRowIndex()] = value;
   };

   int getGridValue(Coor c)
   {
      return grid[c.getColIndex()][c.getRowIndex()];
   }

   int getNumRows( void)
   {
      return num_rows;
   }

   int getNumCols(void)
   {
      return num_cols;
   }

   int getNumColors(void)
   {
      return num_colors;
   }

   void printGrid(void)
   {
      for (int row_index = 0; row_index < num_rows; row_index++)
      {
         for (int col_index = 0; col_index < num_cols; col_index++)
         {
            cout << grid[col_index][row_index];
         }
         cout << "\n";
      }
   }

   int calculateGroupSize(Coor start_search)
   {
      stack<Coor> to_be_checked;
      Coor current, next;
      Gridclass visited = Gridclass(getNumRows(), getNumCols(), getNumColors());
      int group_size = 1;
      char group_color = getGridValue(start_search);

      to_be_checked.push(start_search);

      while(!to_be_checked.empty())
      {
         current = to_be_checked.top();
         to_be_checked.pop();
         visited.setGridValue(current, 'y');
         if (current.getRowIndex() > 0)
         {
            next = current.getUpNb();
            if (getGridValue(next) == group_color
               && visited.getGridValue(next) != 'y')
            {
               to_be_checked.push(next);
               visited.setGridValue(next, 'y');
               group_size++;
            }
         }

         if (current.getRowIndex() < getNumRows() -1)
         {
            next = current.getDownNb();
            if (getGridValue(next) == group_color
               && visited.getGridValue(next) != 'y')
            {
               to_be_checked.push(next);
               visited.setGridValue(next, 'y');
               group_size++;
            }
         }

         if (current.getColIndex() > 0 )
         {
            next = current.getLeftNb();
            if (getGridValue(next) == group_color
               && visited.getGridValue(next) != 'y')
            {
               to_be_checked.push(next);
               visited.setGridValue(next, 'y');
               group_size++;
            }
         }

         if (current.getColIndex() < getNumCols() -1)
         {
            next = current.getRightNb();
            if (getGridValue(next) == group_color
               && visited.getGridValue(next) != 'y')
            {
               to_be_checked.push(next);
               visited.setGridValue(next, 'y');
               group_size++;
            }
         }
      }
      return group_size;
   }
};



Gridclass readGridFromFile(string file_name)
{
   ifstream gridfile;
   int x,y,k;
   Coor c;
   char temp;

   gridfile.open(file_name, ifstream::in);
   gridfile >> x;
   gridfile >> y;
   gridfile >> k;
   Gridclass grid = Gridclass(x, y, k);
   for (int row_index = 0; row_index < x; row_index++)
   {
      for(int col_index = 0; col_index < y; col_index++)
      {
         gridfile >> temp;
         c.setRowIndex(row_index);
         c.setColIndex(col_index);
         grid.setGridValue(c, temp);
      }
   }

   gridfile.close();

   return grid;
}

int main (void)
{
   Gridclass grid = readGridFromFile("ex1.grd");
   return 0;
}
