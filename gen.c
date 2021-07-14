#include <stdio.h>
#include "stdlib.h"

#include "type.h"

int roulette_fitness(IPTR pop, double sumFitness, int popsize);
int roulette_ranking(IPTR pop, RankIndex rankings[], int sumRankings, int popsize);
void crossover_onepoint(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2);
void crossover_twopoint(POPULATION* p, IPTR p1, IPTR p2, IPTR c1, IPTR c2);

double eval(POPULATION *p, IPTR pj);


int cmpfunc(const void* a, const void* b) {
    return (((RankIndex*)a)->fitness - ((RankIndex*)b)->fitness);
}

int generation(POPULATION *p, int t)
{

  int i, p1, p2, c;

  IPTR pi, piPlus1, om1, om2;
  
  RankIndex* rankings = (RankIndex*) malloc(sizeof(RankIndex) * p->popSize);
  for (int i = 0; i < p->popSize; i++) {
      rankings[i].fitness = p->op[i].fitness;
      rankings[i].index = i;
  }
  qsort(rankings, p->popSize, sizeof(RankIndex), cmpfunc);
  for (int i = 0; i < p->popSize; i++) {
      rankings[i].rank = i + 1;
  }

  int sumRankings = ((p->popSize) * (p->popSize + 1)) / 2;

  for (i = 0; i < p->popSize; i += 2) {

      // PARENT SELECTION MODES
      {
          /// Roulette Wheel of Fitnesses
          p1 = roulette_fitness(p->op, p->sumFitness, p->popSize);
          p2 = roulette_fitness(p->op, p->sumFitness, p->popSize);

          /// Roulette Wheel of Rankings
          // p1 = roulette_ranking(p->op, rankings, sumRankings, p->popSize);
          // p2 = roulette_ranking(p->op, rankings, sumRankings, p->popSize);
      }

      pi = &(p->np[i]);
      piPlus1 = &(p->np[i + 1]);
      om1 = &(p->op[p1]);
      om2 = &(p->op[p2]);

      /// CROSSOVER MODES
      {
          /// two point
          // crossover_twopoint(p, om1, om2, pi, piPlus1);

          /// one point
          crossover_onepoint(p, om1, om2, pi, piPlus1);
      }

      /// MUTATION MODES
      {
          /// update mutation probability for simulated annealing mode
          p->pMutCurrent = p->pMutCurrent * 0.95;
          if (p->pMutCurrent < p->pMut)
              p->pMutCurrent = p->pMut;

          /// constant probability of mutation
          // p->pMutCurrent = p->pMut;
      }

    muteX(p, pi, piPlus1);

    pi->fitness = eval(p, pi); 
    pi->parent1 = p1;
    pi->parent2 = p2;

    
    piPlus1->fitness = eval(p, piPlus1); 
    piPlus1->parent1 = p2;
    piPlus1->parent2 = p1;

  }

}

