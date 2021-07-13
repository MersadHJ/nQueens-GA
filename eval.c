#include <stdio.h>
#include <math.h>/* for pow(x, y) */
#include <stdlib.h>
#include "type.h"

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{
  double val = 0;
  int size = p->lchrom;

  for (int i = 0; i < size; i++) 
  {
    int c1 = i + 1;
    int r1 = pj->chrom[i];
    
    for (int j = 0; j < size; j++)
    {
        if (i == j)
            continue;

        int c2 = j + 1;
        int r2 = pj->chrom[j];

        if ((r1 == r2) || (c1 == c2) || (abs(c2 - c1) == abs(r2 - r1)))
        {
            val += 1;
        }
    }
  }
  
  return ((p->lchrom * (p->lchrom - 1)) - val);
}

double decode(IPTR pj, int index, int size)
{
  return ((double) binToDec(&(pj->chrom[0]), size));
}

double binToDec(int *chrom, int l)
{
  int i;
  double prod;

  prod = 0.0;

  for(i = 0; i < l; i++){
    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) i));
  }
  return prod;
}

void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;
  }
}
