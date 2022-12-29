# nQueens-GA
solving nQueens problem using genetic algorithm.
## Usage
The hyperparameters are set in infile with this order:
```
population size
chromosome length (N)
maximum no. of generations.
crossover probability
mutation probability 
output file name
```
for example :
```
50
20
1000
0.66
0.009
ofile.txt
```

After setting these hyperparameters you can run the program by giving the name of the input file to it.

Each individual is a vector of size N filled with a random permutation of numbers between 1 and N.
Each element shows the column of the queen for the element’s index row.

We count the number of clear queens guarding one another in a diagonal issue, and make use of two methods for evaluation, Roulette wheel and Ranking evaluation. The crossover also has two methods, one point and two point crossover.

