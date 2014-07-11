#include <stdio.h>
#include <math.h>
#include <limits.h>

int trueThreeFourths(int x)
{
  int mask = x >> 31;
  int absVal = (mask ^ x) + !!mask;
  int div4 = absVal >> 2;
  int times3 = div4 + div4 + div4;
  int lastTwoBits = x & 3;
  int ltimes3 = lastTwoBits + lastTwoBits + lastTwoBits;
  int res = (ltimes3 >> 2) + times3;

  printf("mask: %x\n", mask);
  printf("absVal: %x\n", absVal);
  printf("res: %x\n", res);
  printf("part1: %x\n",(~mask & res) );
  printf("part2: %x\n", (mask & (~res + 1)));

  return (~mask & res) | (mask & (~res + 1)) | (!(x ^ (1 << 31))  << 31); 
}

int main()
{

  printf("res: %x\n", trueThreeFourths(0x80000000));
}