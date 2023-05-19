#include <stdlib.h>

#include <ai/genome.h>

void initGenome(Genome *g)
{
  g->distance = 0.f;
  g->averageSpeed = 0.f;
  g->checkpointsReached = 0;
  g->timeTaken = 0.f;
}

Genome *generateGenome(GenomeConfig c)
{
  Genome *g = (Genome *)malloc(sizeof(Genome));
  g->weight.distanceWeight = c.distanceWeight;
  g->weight.averageSpeedWeight = c.averageSpeedWeight;
  g->weight.checkpointReachedWeight = c.checkpointReachedWeight;
  g->weight.timeTakenForcheckPointWeight = c.timeTakenForcheckPointWeight;
  initGenome(g);

  return g;
}

float genomeFitness(Genome *g)
{
  float fitnesss = 0.f;
  fitnesss += g->distance * g->weight.distanceWeight;
  fitnesss += g->averageSpeed * g->weight.averageSpeedWeight;
  fitnesss += (float)g->checkpointsReached * g->weight.checkpointReachedWeight;
  fitnesss += g->timeTaken * g->weight.timeTakenForcheckPointWeight;
  return fitnesss / 100.f;
}