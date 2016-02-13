#ifndef __BLOCK_INCLUDED__
#define __BLOCK_INCLUDED__

class Block
{
public:
   char color;
   int groupNumber;
   bool visited;
};

#define EMPTY_BLOCK {'\0', -1, false}
#endif
