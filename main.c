#include <math.h>
#include <stdio.h>
#include "conio.h"
#include "type.h"
int erfunc(char* s, int val);
void initialize(char* argv[], POPULATION* p);
void generation(POPULATION* p, int gen);
void report(int gen, POPULATION* p, IPTR  pop);
void statistics(POPULATION* p, IPTR pop);

main(int argc, char* argv[])
{
    IPTR tmp, op, np;
    POPULATION population;
    POPULATION* p = &population;

    p->gen = 0;
    if (argc != 2) erfunc("Usage: ga <inputfile name> ", argc);
    initialize(argv, p);
    printf(" gen        max        avg        min  HEG HEI        HEF    \n");
    while (p->gen < p->maxGen) {
        p->gen++;
        generation(p, p->gen);
        statistics(p, p->np);
        report(p->gen, p, p->np);
        tmp = p->op;
        p->op = p->np;
        p->np = tmp;
    }

    printf("====================================\n");
    printf(" %3d %3d %10.2lf \n",
        p->highestEverGen,
        p->highestEverIndex,
        p->highestEverFitness);
    for (int i = 0; i < p->lchrom; i++)
    {
        printf("%d,", p->highestEverChrom[i]);
    }
    printf("\n");
}
