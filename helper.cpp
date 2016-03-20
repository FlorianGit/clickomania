#include <iostream>

#include "helper.h"

vector <char> vectorMove(vector <char> orig)
{
   int length = orig.size();
   vector <char> newArray = {};
   for (int i = 0; i < length; i++)
   {
      if (orig[i] != ' ')
         newArray.push_back(orig[i]);
   }
   for (int i =newArray.size(); i < length; i++)
      newArray.push_back(' ');
   return newArray;
}

