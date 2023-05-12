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

  DummyConfig d;
  d.position[0] = 100.f;
  d.position[1] = 530.f;
  d.spritePath = "../../assets/car.png";

  s->dummy = generateDummy(d);
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

    // s->dummy->rotation += 0.1f;
    // sfSprite_setRotation(s->dummy->sprite, s->dummy->rotation);

    // Render world
    renderWorld(s->world, (void *)s->dummy, 1);

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}