#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

typedef struct Context
{
  sfRenderWindow *_window;
  unsigned width;
  unsigned height;
  char *name;
  sfWindowStyle style;
  const sfContextSettings *settings;
} Context;

typedef struct ContextConfig
{
  unsigned width;
  unsigned height;
  char *name;
  sfWindowStyle style;
  const sfContextSettings *settings;
} ContextConfig;

Context *generateContext(ContextConfig config);
void initContext(Context *c);
int isContextOpen(Context *c);
void clearContext(Context *c);
void updateContext(Context *c);
void destroyContext(Context *c);
int contextPollEvent(Context *c, sfEvent *e);
void closeContext(Context *c);

#endif //__CONTEXT_H__