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
  double val;
  int t1 = 0;
  int t2 = 0;
  int size = p->lchrom;
  int* f1 = (int*)malloc(size * (sizeof(int)));
  int* f2 = (int*)malloc(size * (sizeof(int)));
  for (int i = 0; i < size; i++)
  {
      f1[i] = pj->chrom[i] - i;
      f2[i] = (size + 1) - pj->chrom[i] - i;

  }
  qsort(f1, size, sizeof(int), cmp);
  qsort(f2, size, sizeof(int), cmp);
  for (int i = 1; i < size; i++)
  {
    if(f1[i] == f1[i-1]) t1 = t1+1;
    if(f2[i] == f2[i-1]) t2 = t2+1;
  }
  decode(pj, 0, p->lchrom); 
  val = (p->lchrom-1) - (t1 + t2);
  
  return val;
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
