#include <iostream>

#include "helper.h"

vector <Block> vectorMove(vector <Block> orig)
{
   int length = orig.size();
   vector <Block> newArray = {};
   for (int i = 0; i < length; i++)
   {
      if (orig[i].color != ' ')
         newArray.push_back(orig[i]);
   }
   for (int i =newArray.size(); i < length; i++)
      newArray.push_back(EMPTY_BLOCK);
   return newArray;
}


void printBlockVector(vector <Block> v)
{
   for ( int i=0; i< v.size(); i++)
      cout << v[i].color << " ";
   cout << "\n";
}
