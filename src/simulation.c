#include <stdlib.h>
#include <stdio.h>

#include <simulation.h>

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

  // generete ai agent
  AIConfig aiConfig = {s->numOfDummies};
  s->agent = generateAI(aiConfig);

  s->dummies = (Dummy **)malloc(sizeof(Dummy));
  for (int i = 0; i < s->numOfDummies; i++)
  {
    s->dummies[i] = simulationSpawnDummy(s);
    s->dummies[i]->genume = s->agent->population[i];
  }
}

Simulation *generateSimulation(SimulationConfig config)
{
  Simulation *simulation = (Simulation *)malloc(sizeof(Simulation));
  simulation->numOfDummies = config.numOfDummies;

  initSimulation(simulation);
  return simulation;
}

Dummy *simulationSpawnDummy(Simulation *s)
{
  DummyConfig d;
  d.position[0] = 190.f;
  d.position[1] = 540.f;
  d.spritePath = "../../assets/car.png";

  Dummy *dummy;
  dummy = generateDummy(d);

  RadarConfig r;
  r.distance = 70;
  r.position[0] = dummy->position[0];
  r.position[1] = dummy->position[1];
  r.World = s->world;
  Radar *radar = generateRadar(r);

  dummy->radar = radar;

  return dummy;
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

    // Update Dummies
    for (int i = 0; i < s->numOfDummies; i++)
      updateDummy(s->dummies[i]);

    // Render world
    renderWorld(s->world, (void **)s->dummies, s->numOfDummies);

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}