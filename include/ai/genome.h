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
  int sensorsNum;
  int hiddenNum;
  int outputNum;
} GenomeConfig;

/**
 * @brief Fitness metrics
 *
 */
typedef struct
{
  float distance;
  float averageSpeed;
  int checkpointsReached;
  float timeTaken;
} FitnessMetrics;

/**
 * @brief Basic gene structure
 *
 */
typedef struct Genome
{
  FitnessMetrics fitness;
  float **weights_ih;
  float **weights_ho;
  float *biases_h;
  float *biases_o;
} Genome;

/**
 * @brief Initilize the genome
 *
 * @param g : Genome
 * @param sNum : Sensor number
 * @param hNum : hidden layers
 * @param oNum : output layers
 */
void initGenome(Genome *g, int sNum, int hNum, int oNum);

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