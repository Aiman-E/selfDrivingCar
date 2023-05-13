/**
 * @file core.h
 * @brief Defines core macros
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CORE_H__
#define __CORE_H__

#define _USE_MATH_DEFINES
#include <math.h>

#define PIXEL_TO_WORLD(x) x * 100
#define WORLD_TO_PIXEL(x) x / 100
#define TO_DEGREES(x) x * 180.0 / M_PI
#define TO_RAD(x) x *M_PI / 180.0

#endif // __CORE_H__