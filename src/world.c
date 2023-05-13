#include <world.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.h>

#include <dummy.h>

void initWorld(World *w)
{
  sfTexture *backgroundSprite = sfTexture_createFromFile(w->level, NULL);

  w->backgroundSprite = sfSprite_create();
  sfSprite_setTexture(w->backgroundSprite, backgroundSprite, sfTrue);
  sfSprite_setScale(w->backgroundSprite, (sfVector2f){1.3f, 1.3f});

  w->backgroundImage = sfImage_createFromFile(w->level);
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

/**
 * @brief drawing helper function
 *
 * @param w World
 * @param p1 point1
 * @param p2 point2
 */
void drawLine(World *w, sfVector2f p1, sfVector2f p2)
{
  sfVertex line[] =
      {{p1, {0, 0, 0, 0}, {0.f, 0.f}},
       {p2, {0, 0, 0, 0}, {0.f, 0.f}}};
  line[0].color = sfRed;
  line[1].color = sfRed;
  sfRenderWindow_drawPrimitives(w->context->_window, line, 2, sfLines, NULL);
}

void renderWorld(World *w, void *obj, unsigned int count)
{
  sfRenderWindow_drawSprite(w->context->_window, w->backgroundSprite, NULL); // TODO: factor low-level api out
  Dummy *d = (Dummy *)obj;
  sfRenderWindow_drawSprite(w->context->_window, d->sprite, NULL); // TODO: factor low-level api out

  sfVector2f dummyPos = sfSprite_getPosition(d->sprite);
  dummyPos.x /= 1.3f;
  dummyPos.y /= 1.3f;
  updateRadar(d->radar, dummyPos.x, dummyPos.y, d->body->rotation);
  sfVertex *directions = getWallCoords(d->radar);

  for (int i = 0; i < 5; i++)
  {
    drawLine(w,
             (sfVector2f){dummyPos.x * 1.3f, dummyPos.y * 1.3f},
             (sfVector2f){directions[i].position.x * 1.3f, directions[i].position.y * 1.3f});
  }
}
