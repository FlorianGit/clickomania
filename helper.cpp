#include <iostream>

#include "helper.h"

vector <char> vectorMove(vector <char> orig, int length)
{
   vector <char> newArray = {};
   for (int i = 0; i < length; i++)
   {
      if (orig[i] != '\0')
         newArray.push_back(orig[i]);
   }
   for (int i =newArray.size(); i < length; i++)
      newArray.push_back('\0');
   return newArray;
}


void printBlockVector(vector <Block> v)
{
   for ( int i=0; i< v.size(); i++)
      cout << v[i].color << " ";
   cout << "\n";
}
