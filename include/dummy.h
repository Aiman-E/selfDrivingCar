/**
 * @file dummy.h
 * @brief This file is the body of the AI which interact with the world
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __DUMMY_H__
#define __DUMMY_H__

#include <SFML/Graphics.h>

#include <physicsBody.h>

/**
 * @brief Dummy object holds position of dummy, physical body, and sprite
 *
 */
typedef struct Dummy
{
  float position[2];
  PhysicsBody *body;
  char *spritePath;
  sfSprite *sprite;
} Dummy;

/**
 * @brief Configuration object
 *
 */
typedef struct DummyConfig
{
  float position[2];
  char *spritePath;
} DummyConfig;

/**
 * @brief Initialize the dummy
 *
 * @param d : Dummy
 */
void initDummy(Dummy *d);

/**
 * @brief Generate dummy object and allocate it to heap
 *
 * @param c : Dummy
 * @return Dummy*
 */
Dummy *generateDummy(DummyConfig c);

/**
 * @brief Update the dummy position and rotation depending on the physicsBody
 *
 * @param d : Dummy
 */
void updateDummy(Dummy *d);

#endif // __DUMMY_H__