#include <stdlib.h>
#include <time.h>

#include <ai/AI.h>

#define MAGNIFIER 10

void initAI(AI *ai)
{
  generatePopulation(ai);
}

AI *generateAI(AIConfig c)
{
  AI *ai = (AI *)malloc(sizeof(AI));
  ai->populationSize = c.populationSize;

  initAI(ai);
  return ai;
}

void generatePopulation(AI *ai)
{
  Genome **population;
  population = (Genome **)malloc(sizeof(Genome *) * ai->populationSize);
  GenomeConfig genomeConfig;
  genomeConfig.distanceWeight = 2;
  genomeConfig.averageSpeedWeight = 4;
  genomeConfig.checkpointReachedWeight = 5;
  genomeConfig.timeTakenForcheckPointWeight = 3;

  for (int i = 0; i < ai->populationSize; i++)
  {
    population[i] = generateGenome(genomeConfig);
    population[i]->distance = (float)rand() / RAND_MAX * MAGNIFIER;
    population[i]->averageSpeed = (float)rand() / RAND_MAX * MAGNIFIER;
    population[i]->checkpointsReached = rand() % 5; /** @todo change this to map sections*/
    population[i]->timeTaken = (float)rand() / RAND_MAX * MAGNIFIER;
  }

  ai->population = population;
}

void selectParentsFromPopulation(AI *ai, Genome *parent1, Genome *parent2)
{
  int p1, p2 = 0;
  for (int i = 0; i < ai->populationSize; i++)
  {
    float fitness = genomeFitness(ai->population[i]);
    if (fitness > genomeFitness(ai->population[p1]))
    {
      p2 = p1;
      p1 = i;
    }
    else if (fitness > genomeFitness(ai->population[p2]))
    {
      p2 = i;
    }
  }

  parent1 = ai->population[p1];
  parent2 = ai->population[p2];
}

Genome crossover(Genome *p1, Genome *p2)
{
  Genome offspring;

  offspring.distance = (p1->distance + p2->distance) / 2.0f;
  offspring.averageSpeed = (p1->averageSpeed + p2->averageSpeed) / 2.0f;
  offspring.checkpointsReached = (int)((p1->checkpointsReached + p2->checkpointsReached) / 2);
  offspring.timeTaken = (p1->timeTaken + p2->timeTaken) / 2.0f;

  return offspring;
}

void mutate(Genome *g, float mutationRate)
{
  srand(time(NULL)); // seed the generator

  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->distance += (float)rand() / RAND_MAX * 10;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->averageSpeed += (float)rand() / RAND_MAX * 10;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->checkpointsReached = !g->checkpointsReached * 10;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->timeTaken += (float)rand() / RAND_MAX;
  }
}

void evolveAI(AI *ai)
{
  srand(time(NULL)); // seed the generator

  Genome *newPopulation = malloc(sizeof(Genome) * ai->populationSize);

  Genome parents[2];
  selectParentsFromPopulation(ai, &parents[0], &parents[1]);

  for (int i = 0; i < ai->populationSize; i++)
  {
    Genome offspring = crossover(&parents[0], &parents[1]);

    mutate(&offspring, 0.3);

    newPopulation[i] = offspring;
  }

  newPopulation[0] = parents[0];
  newPopulation[1] = parents[1];

  free(ai->population);
  ai->population = newPopulation;
}
