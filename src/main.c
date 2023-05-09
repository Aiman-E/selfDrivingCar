#include <simulation.h>

int main()
{
  SimulationConfig simulationConfig = {10};
  Simulation *simulation = generateSimulation(simulationConfig);

  simulationMainLoop(simulation);

    return 0;
}