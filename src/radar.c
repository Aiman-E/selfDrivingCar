#include <stdlib.h>

#include <radar.h>
#include <core.h>
#include <SFML/Graphics.h>

void initRadar(Radar *r)
{
  r->directions[0].position = (sfVector2f){0.f, 0.f};
  r->directions[1].position = (sfVector2f){0.f, 0.f};
  r->directions[2].position = (sfVector2f){0.f, 0.f};
  r->directions[3].position = (sfVector2f){0.f, 0.f};
  r->directions[4].position = (sfVector2f){0.f, 0.f};

  r->directions[0].color = sfRed;
  r->directions[1].color = sfRed;
  r->directions[2].color = sfRed;
  r->directions[3].color = sfRed;
  r->directions[4].color = sfRed;

  r->rotation = 0.0;
}

Radar *generateRadar(RadarConfig c)
{
  Radar *r = (Radar *)malloc(sizeof(Radar));
  r->World = c.World;
  r->distance = c.distance;
  r->position[0] = c.position[0];
  r->position[1] = c.position[1];

  initRadar(r);
  return r;
}

sfVertex *getWallCoords(Radar *r)
{
  // Front
  for (float x = 0.f; x <= r->distance; x++)
  {
    sfVector2f d = {r->position[0] + x * cos(r->rotation),
                    r->position[1] + x * sin(r->rotation)};

    unsigned char front = sfImage_getPixel(r->World->backgroundImage, d.x, d.y).r;
    if (front != 0)
    {
      r->directions[0].position = d;
      break;
    }
  }

  // left
  for (float x = 0.f; x <= r->distance; x++)
  {
    sfVector2f d = {r->position[0] + x * sin(r->rotation),
                    r->position[1] - x * cos(r->rotation)};
    unsigned char left = sfImage_getPixel(r->World->backgroundImage, d.x, d.y).r;
    if (left != 0)
    {
      r->directions[1].position = d;
      break;
    }
  }

  // right
  for (float x = 0.f; x <= r->distance; x++)
  {
    sfVector2f d = {r->position[0] - x * sin(r->rotation),
                    r->position[1] + x * cos(r->rotation)};
    unsigned char right = sfImage_getPixel(r->World->backgroundImage, d.x, d.y).r;
    if (right != 0)
    {
      r->directions[2].position = d;
      break;
    }
  }

  // left angled
  for (float x = 0.f; x <= r->distance; x++)
  {
    sfVector2f d = {r->position[0] + x * sin(r->rotation + TO_RAD(45.0)),
                    r->position[1] - x * cos(r->rotation + TO_RAD(45.0))};
    unsigned char leftAngled = sfImage_getPixel(r->World->backgroundImage, d.x, d.y).r;
    if (leftAngled != 0)
    {
      r->directions[3].position = d;
      break;
    }
  }

  // right angled
  for (float x = 0.f; x <= r->distance; x++)
  {
    sfVector2f d = {r->position[0] - x * sin(r->rotation - TO_RAD(45.0)),
                    r->position[1] + x * cos(r->rotation - TO_RAD(45.0))};
    unsigned char right = sfImage_getPixel(r->World->backgroundImage, d.x, d.y).r;
    if (right != 0)
    {
      r->directions[4].position = d;
      break;
    }
  }

  return r->directions;
}

unsigned char hasCollided(Radar *r)
{
  unsigned char pos = sfImage_getPixel(r->World->backgroundImage, r->position[0], r->position[1]).r;
  return pos ? 1 : 0;
}

void updateRadar(Radar *r, float x, float y, float rotation)
{
  r->position[0] = x;
  r->position[1] = y;
  r->rotation = rotation;
}