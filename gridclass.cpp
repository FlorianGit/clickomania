#include "coorclass.h"
#include "gridclass.h"
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

Gridclass::Gridclass(int num_r, int num_c, int num_clrs)
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

Gridclass::~Gridclass(void)
{
   for(int col_index = 0; col_index < num_cols; col_index++){
      free(grid[col_index]);
   }
   free(grid);
}

void Gridclass::printGrid(void)
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

int Gridclass::calculateGroupSize(Coor start_search)
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
