#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class Gridclass {
   int num_rows;
   int num_cols;
   int num_colors;
   char** grid;

   public:
      Gridclass(int num_rows, int num_cols, int num_colors);
      ~Gridclass( void );
      void setGridValue(int col_index, int row_index, char value)
      {
         grid[row_index][col_index] = value;
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
   char temp;

   gridfile.open(file_name);
   gridfile >> x >> y >> k;
   Gridclass grid = Gridclass(x, y, k);
   for (int row_index; row_index < x; row_index++)
   {
      for(int col_index; col_index < y; col_index++)
      {
         gridfile >> temp;
         grid.setGridValue(row_index, col_index, temp);
      }
   }

   gridfile.close();

   return grid;
}

int main (void)
{
   printf("Hello world 3\n");
   Gridclass grid = readGridFromFile("ex1.grd");
   printf("Hoi");
   return 0;
}
