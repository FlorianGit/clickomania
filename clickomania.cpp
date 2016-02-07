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

   Coor getUpNb(Coor c)
   {
      Coor nb = Coor(c.getRowIndex() -1, c.getColIndex());
      return nb;
   };

   Coor getDownNb(Coor c)
   {
      Coor nb = Coor(c.getRowIndex() + 1, c.getColIndex());
      return nb;
   };

   Coor getLeftNb(Coor c)
   {
      Coor nb = Coor(c.getRowIndex(), c.getColIndex() - 1);
      return nb;
   };

   Coor getRightNb(Coor c)
   {
      Coor nb = Coor(c.getRowIndex(), c.getColIndex() + 1);
      return nb;
   };
};

class Gridclass {
   int num_rows;
   int num_cols;
   int num_colors;
   char** grid;

   public:
      Gridclass(int num_rows, int num_cols, int num_colors);
      ~Gridclass( void );
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

      int getGroupSize(Gridclass grid, Coor start_search)
      {
         stack<Coor> to_be_checked;
         Gridclass visited = Gridclass(grid.getNumRows(), grid.getNumCols(), grid.getNumColors());
         int group_size = 1;
         char group_color = grid.getGridValue(start_search);

         to_be_checked.push(start_search);
         visited.setGridValue(start_search, 'y');

      }
};

Gridclass::Gridclass(int num_r, int num_c, int num_clrs)
{
   num_rows = num_r;
   num_cols = num_c;
   num_colors = num_clrs;
   grid = (char**)malloc(num_cols * sizeof(char*));
   for (int col_index = 0; col_index < num_cols; col_index++){
      grid[col_index] = (char*)malloc(num_rows * sizeof(char));
   }
}

Gridclass::~Gridclass(void)
{
   for(int col_index = 0; col_index < num_cols; col_index++){
      free(grid[col_index]);
   }
   free(grid);
}

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
   grid.printGrid();
   return 0;
}
