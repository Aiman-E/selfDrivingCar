#include <stdlib.h>
#include <math.h>

#include <ai/genome.h>

#define getRandomNumber() (float)rand() / RAND_MAX

void initGenome(Genome *g, int sNum, int hNum, int oNum)
{
  g->fitness.distance = 0.f;
  g->fitness.averageSpeed = 0.f;
  g->fitness.checkpointsReached = 0;
  g->fitness.timeTaken = 0.f;

  for (int i = 0; i < sNum; i++)
    for (int j = 0; j < hNum; j++)
      g->weights_ih[i][j] = getRandomNumber();

  for (int i = 0; i < hNum; i++)
  {
    g->biases_h[i] = getRandomNumber();
    for (int j = 0; j < oNum; j++)
    {
      g->biases_o[j] = getRandomNumber();
      g->weights_ho[i][j] = getRandomNumber();
    }
  }
}

Genome *generateGenome(GenomeConfig c)
{
  Genome *g = (Genome *)malloc(sizeof(Genome));
  g->weights_ih = (float **)malloc(sizeof(float *) * c.sensorsNum);
  for (int i = 0; i < c.sensorsNum; i++)
    g->weights_ih[i] = (float *)malloc(sizeof(float) * c.hiddenNum);

  g->weights_ho = (float **)malloc(sizeof(float *) * c.hiddenNum);
  for (int i = 0; i < c.hiddenNum; i++)
    g->weights_ih[i] = (float *)malloc(sizeof(float) * c.outputNum);

  g->biases_h = (float *)malloc(sizeof(float) * c.hiddenNum);
  g->biases_o = (float *)malloc(sizeof(float) * c.outputNum);
  initGenome(g, c.sensorsNum, c.hiddenNum, c.outputNum);

  return g;
}

float genomeFitness(Genome *g)
{
  float fitnesss = 0.f;
  fitnesss += g->fitness.distance;
  fitnesss += g->fitness.averageSpeed;
  fitnesss += g->fitness.checkpointsReached;
  fitnesss += g->fitness.timeTaken;
  return fitnesss;
}