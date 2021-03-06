#ifndef POSITION_TRACKER_H_
#define POSITION_TRACKER_H_

#include "../main.h"

namespace position_tracker {

  // chassis characteristics
  #define TRACKER_DIST 15.25f // distance between left/right tracker wheels (inches)
  #define SIDE_DIST 7.5f // distance from center of rotation to sideways tracker wheel (inches)
  #define WHEEL_SIZE 4.125f // diameter of tracking wheels (inches)

  // conversion factors
  inline float ANGLE_TO_DIST(float angle) {return WHEEL_SIZE * PI * angle/360.f;} // convert angle (degrees) to dist (inches)
  inline float DIST_TO_ANGLE(float dist) {return dist * 360.f / (WHEEL_SIZE * PI);} // convert dist (inches) to angle (degrees)
  inline float ORIENTATION_FROM_SIDE_DIST(float dist_l, float dist_r) {return (dist_r - dist_l) / TRACKER_DIST;} // calculate absolute orientation (radians) from left/right distances (inches)

  // sensors
  extern pros::ADIEncoder* enc_left; // encoder attached to left tracker wheel
  extern pros::ADIEncoder* enc_right; // encoder attached to right tracker wheel
  extern pros::ADIEncoder* enc_side; // encoder attached to sideways tracker wheel

  // state
  extern float x; // position along x axis (inches)
  extern float x_vel; // velocity along x axis (inches/sec)
  extern float y; // position along y axis (inches)
  extern float y_vel; // velocity along y axis (inches/sec)
  extern long double orientation; // orientation (radians)
  extern float orientation_deg; // orientation (degrees)
  extern long double angular_vel; // angular velocity (deg/sec)

  // initialize
  void init(float _x, float _y, float _orientation);

  // update
  void update(int delta_t);

}

#endif