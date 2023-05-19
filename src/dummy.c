#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

#include <dummy.h>
#include <core.h>

void initDummy(Dummy *d)
{
  d->alive = 1;
  d->startingTime = time(0);

  sfTexture *sprite = sfTexture_createFromFile(d->spritePath, NULL);
  d->sprite = sfSprite_create();
  sfSprite_setTexture(d->sprite, sprite, sfTrue);
  sfSprite_setPosition(d->sprite, (sfVector2f){d->position[0], d->position[1]});
  sfSprite_setRotation(d->sprite, -90);
  sfSprite_setOrigin(d->sprite, (sfVector2f){320 / 2, 613 / 2}); // This is missed up :)
  sfSprite_setScale(d->sprite, (sfVector2f){.03f, .03f});
}

Dummy *generateDummy(DummyConfig c)
{
  Dummy *d = (Dummy *)malloc(sizeof(Dummy));
  d->position[0] = c.position[0];
  d->position[1] = c.position[1];
  PhysicsBodyConfig bodyConfig = {1, 3};
  d->body = generatePhysicsBody(bodyConfig);

  d->spritePath = c.spritePath;

  initDummy(d);
  return d;
}

void updateDummy(Dummy *d)
{
  // Drawing updates
  d->position[0] += WORLD_TO_PIXEL(d->body->velocity.x);
  d->position[1] += WORLD_TO_PIXEL(d->body->velocity.y);
  sfSprite_setPosition(d->sprite, (sfVector2f){
                                      d->position[0],
                                      d->position[1]});
  sfSprite_setRotation(d->sprite, TO_DEGREES(d->body->rotation) + 90);

  // genome updates
  d->genume->averageSpeed += d->body->speed;
}

unsigned char dummyCheckCollision(Dummy *d)
{
  return hasCollided(d->radar);
}

void stopDummy(Dummy *d)
{
  stopPhysicsBody(d->body);
  d->endingTime = time(0);
}