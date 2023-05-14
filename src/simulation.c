#include <simulation.h>
#include <stdlib.h>
#include <stdio.h>

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

  s->dummy = simulationSpawnDummy(s);
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
  d.position[0] = 200.f;
  d.position[1] = 540.f;
  d.spritePath = "../../assets/car.png";

  s->dummy = generateDummy(d);

  RadarConfig r;
  r.distance = 70;
  r.position[0] = s->dummy->position[0];
  r.position[1] = s->dummy->position[1];
  r.World = s->world;
  Radar *radar = generateRadar(r);

  s->dummy->radar = radar;
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

      if (sfKeyboard_isKeyPressed(sfKeyW))
      {
        acceleratePhysicsBody(s->dummy->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyS))
      {
        deacceleratePhysicsBody(s->dummy->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyD))
      {
        rotateRightPhysicsBody(s->dummy->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyA))
      {
        rotateLeftPhysicsBody(s->dummy->body);
        break;
      }
    }

    /* Clear the screen */
    clearContext(s->context);

    // Update Dummies
    updateDummy(s->dummy);

    // Render world
    renderWorld(s->world, (void *)s->dummy, 1);

    printf("%f\n", s->dummy->radar->power[1]);

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}

unsigned char checkCollision(Simulation *s)
{
  return hasCollided(s->dummy->radar);
}