#ifndef __WORLD_H__
#define __WORLD_H__

#include <Context.h>

typedef struct WorldConfig
{
  char *level;
  Context *context;
} WorldConfig;

typedef struct World
{
  char *level;
  Context *context;
  sfSprite *background;
} World;

World *generateWorld(WorldConfig config);
void initWorld(World *w);
void renderWorld(World *w);

#endif //__WORLD_H__