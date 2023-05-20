#ifndef __AI_H__
#define __AI_H__

#include <ai/genome.h>
#include <SFML/Graphics.h>

typedef enum ACTIONS
{
  FRONT,
  LEFT,
  RIGHT,
  BRAKE
} ACTIONS;

typedef struct AIConfig
{
  unsigned int populationSize;
} AIConfig;

typedef struct AI
{
  Genome **population;
  unsigned int populationSize;
} AI;

/**
 * @brief Generate AI
 *
 * @param c : configuration
 * @return AI*
 */
AI *generateAI(AIConfig c);

/**
 * @brief Initialize AI object
 *
 * @param ai : AI
 */
void initAI(AI *ai);

/**
 * @brief generate population and initialize it with random genes
 *
 * @param ai : AI
 */
void generatePopulation(AI *ai);

/**
 * @brief select the genome with the highest fitness value for next generation
 *
 * @param ai : AI
 * @return int* : index number of parents
 */
int *selectParentsFromPopulation(AI *ai);

/**
 * @brief Mix parent genes and return an offspring
 *
 * @param p1 : Parent 1
 * @param p2 : Parent 2
 * @return Genome*
 */
Genome *crossover(Genome *p1, Genome *p2);

/**
 * @brief mutate genes randomly
 *
 * @param g : Genome
 * @param mutationRate : mutation rate (value between 0 - 1)
 * @return Genome
 */
Genome mutation(Genome *g, float mutationRate);

/**
 * @brief evovle the populaiton
 *
 * @param ai : ai
 */
void evolveAI(AI *ai);

#endif //__AI_H__
