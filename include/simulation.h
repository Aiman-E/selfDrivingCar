#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <context.h>
#include <world.h>

typedef struct Simulation
{
  Context *context;
  World *world;
  unsigned int numOfDummies;
} Simulation;

typedef struct SimulationConfig
{
  unsigned int numOfDummies;
} SimulationConfig;

void initSimulation(Simulation *s);
Simulation *generateSimulation(SimulationConfig config);
void simulationMainLoop(Simulation *s);

// TODO: SPAWNING
// void startGeneration();
// void endGeneration();
// void spawnDummy();
// void destroyDummy();

#endif // __SIMULATION_H__