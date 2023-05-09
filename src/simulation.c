#include <simulation.h>
#include <stdlib.h>

void initSimulation(Simulation *s)
{
  ContextConfig contextConfig = {
      800, 600, "AI Car", sfResize | sfClose, NULL};
  s->context = generateContext(contextConfig);

  // generate world
  WorldConfig worldConfig = {
      "../../assets/stage.png",
      s->context};
  s->world = generateWorld(worldConfig);
}

Simulation *generateSimulation(SimulationConfig config)
{
  Simulation *simulation = (Simulation *)malloc(sizeof(Simulation));
  simulation->numOfDummies = config.numOfDummies;

  initSimulation(simulation);
  return simulation;
}

void simulationMainLoop(Simulation *s)
{
  /* Start the game loop */
  while (isContextOpen(s->context))
  {
    sfEvent e;
    while (contextPollEvent(s->context, &e))
    {
      switch (e.type)
      {
      case sfEvtClosed:
        closeContext(s->context);
        break;
      }
    }

    /* Clear the screen */
    clearContext(s->context);

    // Render world
    renderWorld(s->world);

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}