/**
 * @file genome.h
 * @brief Defines basic genes
 * @version 0.1
 * @date 2023-05-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __GENOME_H__
#define __GENOME_H__

/**
 * @brief Genome configuration
 *
 */
typedef struct GenomeConfig
{
  float distanceWeight;
  float averageSpeedWeight;
  float checkpointReachedWeight;
  float timeTakenForcheckPointWeight;
} GenomeConfig;

/**
 * @brief Achievment weights
 *
 */
typedef struct AchievementWeights
{
  float distanceWeight;
  float averageSpeedWeight;
  float checkpointReachedWeight;
  float timeTakenForcheckPointWeight;
} AchievementWeights;

/**
 * @brief Basic gene structure
 *
 */
typedef struct Genome
{
  AchievementWeights weight;
  float distance;
  float averageSpeed;
  int checkpointsReached;
  float timeTaken;
} Genome;

/**
 * @brief  Initialize the genome
 *
 * @param g : Genome
 */
void initGenome(Genome *g);

/**
 * @brief Generate genome and allocate it to heap
 *
 * @param c : Configuration
 * @return Genome*
 */
Genome *generateGenome(GenomeConfig c);

/**
 * @brief Calculate the fitness value
 *
 * @param g : Genome
 * @return float
 */
float genomeFitness(Genome *g);

#endif // __GENOME_H__