/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "pros/apix.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "common_values.hpp"

extern bool intake_auto;
extern bool flip_auto;
extern bool lift_auto;

static inline float sign(float x) {
  return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

static inline float min(float a, float b) {
  return (a < b) ? a : b;
}

static inline float max(float a, float b) {
  return (a > b) ? a : b;
}

static inline float clamp(float val, float min, float max) {
  if (val < min) return min;
  if (val > max) return max;
  return val;
}

void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);

#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
#endif
#endif
