#include <stdlib.h>

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
  Genome *population[ai->populationSize];
  GenomeConfig genomeConfig;
  genomeConfig.distanceWeight = 1;
  genomeConfig.averageSpeedWeight = 1;
  genomeConfig.checkpointReachedWeight = 0;
  genomeConfig.timeTakenForcheckPointWeight = 0;

  for (int i = 0; i < ai->populationSize; i++)
  {
    population[i] = generateGenome(genomeConfig);
    population[i]->distance = (float)rand() / RAND_MAX * MAGNIFIER;
    population[i]->averageSpeed = (float)rand() / RAND_MAX * MAGNIFIER;
    population[i]->death = (float)rand() / RAND_MAX * MAGNIFIER > 5 ? 1 : 0;
    population[i]->checkpointsReached = rand() % 5; /** @todo change this to map sections*/
    population[i]->timeTaken = (float)rand() / RAND_MAX * MAGNIFIER;
  }

  ai->population = population;
}

Genome **selectpsFromPopulation(AI *ai)
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

  Genome *parents[] = {ai->population[p1], ai->population[p2]};

  return parents;
}

Genome crossover(Genome *p1, Genome *p2)
{
  Genome offspring;

  offspring.distance = (p1->distance + p2->distance) / 2.0f;
  offspring.averageSpeed = (p1->averageSpeed + p2->averageSpeed) / 2.0f;
  offspring.death = p1->death || p2->death;
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
    g->death = g->death ? 0 : 1;
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