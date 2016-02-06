#include <stdio.h>
#include <cstdlib>

class Grid {
   int num_rows;
   int num_cols;
   int num_colors;
   int** grid;

   Grid(int num_rows, int num_cols, int num_colors, int**grid);
   ~Grid( void );
};

Grid::Grid(int num_r, int num_c, int num_clrs, int** grd)
{
   num_rows = num_r;
   num_cols = num_c;
   num_colors = num_clrs;
   grd = (int**)malloc(num_cols * sizeof(int*));
   for (int col_index = 0; col_index < num_cols; col_index++){
      grd[col_index] = (int*)malloc(num_rows * sizeof(int));
   }
}

Grid::~Grid(void)
{
   for(int col_index = 0; col_index < num_cols; col_index++){
      free(grid[col_index]);
   }
   free(grid);
}

/*Grid readGridFromFile(char* file_name)
{
   size_t len = 0;
   char *line = NULL;

   FILE* fp = fopen(file_name, "r");
   getline(&line, &len, fp);

}*/

int main (void)
{
   printf("Hello world 3\n");
   return 0;
}
