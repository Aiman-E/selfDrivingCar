#ifndef __AI_H__
#define __AI_H__

#include <ai/genome.h>
#include <SFML/Graphics.h>

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
 * @return Genome**
 */
Genome **selectParentsFromPopulation(AI *ai);

/**
 * @brief Mix parent genes and return an offspring
 *
 * @param p1
 * @param p2
 * @return Genome
 */
Genome crossover(Genome *p1, Genome *p2);

/**
 * @brief mutate genes randomly
 *
 * @param g : Genome
 * @param mutationRate : mutation rate (value between 0 - 1)
 * @return Genome
 */
Genome mutation(Genome *g, float mutationRate);

#endif //__AI_H__
