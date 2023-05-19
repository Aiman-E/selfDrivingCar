#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

  s->dummies = (Dummy **)malloc(sizeof(Dummy *) * s->numOfDummies);
  for (int i = 0; i < s->numOfDummies; i++)
  {
    s->dummies[i] = simulationSpawnDummy(s);
    s->dummies[i]->genume = *(s->agent->population + i);
  }

  s->dummiesLeft = s->numOfDummies;
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
  d.position[0] = 75.f;
  d.position[1] = 550.f;
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

      if (sfKeyboard_isKeyPressed(sfKeyW))
      {
        acceleratePhysicsBody(s->dummies[0]->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyS))
      {
        deacceleratePhysicsBody(s->dummies[0]->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyD))
      {
        rotateRightPhysicsBody(s->dummies[0]->body);
        break;
      }

      if (sfKeyboard_isKeyPressed(sfKeyA))
      {
        rotateLeftPhysicsBody(s->dummies[0]->body);
        break;
      }
    }

    /* Clear the screen */
    clearContext(s->context);

    // Render world
    renderWorld(s->world, (void **)s->dummies, s->numOfDummies);

    // Update Dummies
    for (int i = 0; i < s->numOfDummies; i++)
    {
      updateDummy(s->dummies[i]);
      checkCollision(s, s->dummies[i]);
    }

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}

void dummyInsideCheckpoint(Simulation *s, Dummy *d, int i)
{
  if (d->position[0] >= s->world->checkpointPosition[i][0].x &&
      d->position[0] <= s->world->checkpointPosition[i][0].x + s->world->checkpointPosition[i][1].x &&
      d->position[1] >= s->world->checkpointPosition[i][0].y &&
      d->position[1] <= s->world->checkpointPosition[i][0].y + abs(s->world->checkpointPosition[i][1].y))
  {
    d->genume->checkpointsReached++;
  }
}

void checkCollision(Simulation *s, Dummy *d)
{
  if (dummyCheckCollision(d) && d->alive)
  {
    stopDummy(d);
    d->alive = 0;
    s->dummiesLeft--;

    d->genume->timeTaken = d->endingTime - d->startingTime;
    d->genume->distance = d->genume->averageSpeed;
    d->genume->averageSpeed /= d->genume->timeTaken;
  }
}