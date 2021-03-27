#include "type.h"

int rnd(int low, int high);
int flip(double);
int muteX(POPULATION *p, int pa, int pb);

void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp, i;

  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;
  
  int size = p->lchrom;
  if(flip(p->pCross)){
    int lb = rand() % size;
    int hb = rand() % size;
    if (lb > hb) 
    {
    int temp = lb;
    lb = hb;
    hb = temp;
    }

    int bools1 = 0;
    int bools2 = 0;
    for(int i=lb; i<=hb; i++)
    {
        ci1[i] = pi1[i];
        bools1 |= 1 << pi1[i];
        ci2[i] = pi2[i];
        bools2 |= 1 << pi2[i];    
    }
    for(int i=0; i<lb; i++)
    {
        for(int j=0; j<size; j++)
        {                                  
            if(bools1 & (1 << pi2[j]) == 0)
            {
                ci1[i] = pi2[j];
                bools1 |= 1 << pi2[j];
                break;
            }
        }
        for(int j=0; j<size; j++)
        {                                  
            if(bools2 & (1 << pi1[j]) == 0)
            {
                ci2[i] = pi1[j];
                bools2 |= 1 << pi1[j];
                break;
            }
        }
    }
    for(int i=hb+1; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {                                  
            if(bools1 & (1 << pi2[j]) == 0)
            {
                ci1[i] = pi2[j];
                bools1 |= 1 << pi2[j];
                break;
            }
        }
        for(int j=0; j<size; j++)
        {                                  
            if(bools2 & (1 << pi1[j]) == 0)
            {
                ci2[i] = pi1[j];
                bools2 |= 1 << pi1[j];
                break;
            }
        }
    }

    //xp = rnd(0, p->lchrom - 1);
    //for(i = 0; i < xp; i++){
    //  ci1[i] = muteX(p, pi1[i],pi2[i]);
    //  ci2[i] = muteX(p, pi2[i],pi1[i]);
    //}
    //for(i = xp; i < p->lchrom; i++){
    //  ci1[i] = muteX(p, pi2[i],pi1[i]);
    //  ci2[i] = muteX(p, pi1[i],pi2[i]);
    //}
  }
  else {
    for(i = 0; i < p->lchrom; i++){
      ci1[i] = pi1[i];
      ci2[i] = pi2[i];
    }
  }

  for (int k = 0; k < size / 4; k++)
  {
      if (flip(p->pMut))
      {
          int m11 = rand() % size;
          int m12 = rand() % size;

          int temp;

          temp = ci1[m11];
          ci1[m11] = ci1[m12];
          ci1[m12] = temp;
      }

      if (flip(p->pMut))
      {
          int m21 = rand() % size;
          int m22 = rand() % size;

          int temp;

          temp = ci2[m21];
          ci2[m21] = ci2[m22];
          ci2[m22] = temp;
      }
  }

}

int muteX(POPULATION *p, int pa, int pb)
{
  return (flip(p->pMut) ? pa  : pb);
}



