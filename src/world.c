#include <world.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.h>

#include <dummy.h>

void initWorld(World *w)
{
  sfTexture *background = sfTexture_createFromFile(w->level, NULL);

  w->background = sfSprite_create();
  sfSprite_setTexture(w->background, background, sfTrue);
  sfSprite_setScale(w->background, (sfVector2f){1.3f, 1.3f});
}

World *generateWorld(WorldConfig c)
{
  World *world = (World *)malloc(sizeof(World));
  world->level = (char *)malloc(sizeof(c.level));
  world->level = c.level;

  world->context = c.context;

  initWorld(world);

  return world;
}

void renderWorld(World *w, void *obj, unsigned int count)
{
  Dummy *d = (Dummy *)obj;
  sfRenderWindow_drawSprite(w->context->_window, w->background, NULL); // TODO: factor low-level api out
  sfRenderWindow_drawSprite(w->context->_window, d->sprite, NULL);     // TODO: factor low-level api out
}