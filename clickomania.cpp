#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

struct coor {
   int col_index;
   int row_index;
};

class Gridclass {
   int num_rows;
   int num_cols;
   int num_colors;
   char** grid;

   public:
      Gridclass(int num_rows, int num_cols, int num_colors);
      ~Gridclass( void );
      void setGridValue(coor c, char value)
      {
         grid[c.col_index][c.row_index] = value;
      };

      int getGridValue(coor c)
      {
         return grid[c.col_index][c.row_index];
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

/*      int getGroupSize(int row_index, int col_index)
      {
         stack<*/
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
   coor c;
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
         c.row_index = row_index;
         c.col_index = col_index;
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
