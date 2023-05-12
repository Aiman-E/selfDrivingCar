#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

#include <dummy.h>
#include <core.h>

#define TO_DEGREES(x) x * 180.0 / M_PI

void initDummy(Dummy *d)
{
  sfTexture *sprite = sfTexture_createFromFile(d->spritePath, NULL);
  d->sprite = sfSprite_create();
  sfSprite_setTexture(d->sprite, sprite, sfTrue);
  sfSprite_setPosition(d->sprite, (sfVector2f){d->position[0], d->position[1]});
  sfSprite_setRotation(d->sprite, -90);
  sfSprite_setOrigin(d->sprite, (sfVector2f){320 / 2, 613 / 2}); // This is missed up :)
  sfSprite_setScale(d->sprite, (sfVector2f){.05f, .05f});
}

Dummy *generateDummy(DummyConfig c)
{
  Dummy *d = (Dummy *)malloc(sizeof(Dummy));
  d->position[0] = c.position[0];
  d->position[1] = c.position[1];
  PhysicsBodyConfig bodyConfig = {0.2, 0.2};
  d->body = generatePhysicsBody(bodyConfig);

  d->spritePath = c.spritePath;

  initDummy(d);
  return d;
}

void updateDummy(Dummy *d)
{
  d->position[0] += WORLD_TO_PIXEL(d->body->velocity.x);
  d->position[1] += WORLD_TO_PIXEL(d->body->velocity.y);
  sfSprite_setPosition(d->sprite, (sfVector2f){
                                      d->position[0],
                                      d->position[1]});
  sfSprite_setRotation(d->sprite, TO_DEGREES(d->body->rotation) - 90);
}
