
#include "type.h"

double f_random();

int roulette_fitness(IPTR pop, double sumFitness, int popsize)
{ 

  /* select a single individual by roulette wheel selection */
  
  double rand,partsum;
  int i;

  partsum = 0.0; 
  rand = f_random() * sumFitness; 
  
  i = -1;
  do{
    i++;
    partsum += pop[i].fitness;
  } while (partsum < rand && i < popsize - 1) ;
  
  return i;
}

int roulette_ranking(IPTR pop, RankIndex rankings[], int sumRankings, int popsize)
{
    /* select a single individual by roulette wheel selection */

    double rand, partsum;
    int r;

    partsum = 0.0;
    rand = f_random() * sumRankings;

    r = popsize + 1;
    do {
        r--;
        partsum += r;
    } while (partsum < rand);

    int i;
    for (i = 0; i < popsize; i++)
        if (rankings[i].rank == r)
            break;

    return rankings[i].index;
}
