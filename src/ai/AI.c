#include <stdlib.h>
#include <time.h>

#include <ai/AI.h>

void initAI(AI *ai)
{
  generatePopulation(ai);
}

AI *generateAI(AIConfig c)
{
  AI *ai = (AI *)malloc(sizeof(AI));
  ai->populationSize = c.populationSize;
  ai->population = (Genome **)malloc(sizeof(Genome *) * ai->populationSize);

  initAI(ai);
  return ai;
}

void generatePopulation(AI *ai)
{
  GenomeConfig genomeConfig;
  genomeConfig.sensorsNum = 5;
  genomeConfig.hiddenNum = 4;
  genomeConfig.outputNum = 4;

  for (int i = 0; i < ai->populationSize; i++)
  {
    ai->population[i] = generateGenome(genomeConfig);
  }
}

int *selectParentsFromPopulation(AI *ai)
{
  int p1, p2 = 0;
  int *Ps = (int *)malloc(sizeof(int) * 2);

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

  Ps[0] = p1;
  Ps[1] = p2;
  return Ps;
}

Genome *crossover(Genome *p1, Genome *p2)
{
  Genome *offspring = (Genome *)malloc(sizeof(Genome));

  offspring->fitness.distance = (p1->fitness.distance + p2->fitness.distance) / 2.0f;
  offspring->fitness.averageSpeed = (p1->fitness.averageSpeed + p2->fitness.averageSpeed) / 2.0f;
  offspring->fitness.checkpointsReached = (int)((p1->fitness.checkpointsReached + p2->fitness.checkpointsReached) / 2);
  offspring->fitness.timeTaken = (p1->fitness.timeTaken + p2->fitness.timeTaken) / 2.0f;

  return offspring;
}

void mutate(Genome *g, float mutationRate)
{
  srand(time(NULL)); // seed the generator

  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.distance += (float)(rand() / RAND_MAX) * g->fitness.distance;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.averageSpeed += (float)rand() / RAND_MAX * g->fitness.averageSpeed;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.checkpointsReached += (float)rand() / RAND_MAX * g->fitness.checkpointsReached;
    if (g->fitness.checkpointsReached >= 45)
      g->fitness.checkpointsReached = 45;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.timeTaken += (float)rand() / RAND_MAX;
  }
}

void evolveAI(AI *ai)
{
  srand(time(NULL)); // seed the generator

  Genome **newPopulation = malloc(sizeof(Genome *) * ai->populationSize);

  int *parentIndex = selectParentsFromPopulation(ai);

  for (int i = 0; i < ai->populationSize; i++)
  {
    Genome *offspring = crossover(ai->population[parentIndex[0]], ai->population[parentIndex[1]]);

    mutate(offspring, 0.3);

    newPopulation[i] = offspring;
  }

  newPopulation[0] = ai->population[parentIndex[0]];
  newPopulation[1] = ai->population[parentIndex[1]];

  free(parentIndex);
  free(ai->population);
  ai->population = newPopulation;
}
