#include "../../include/field_managers/ball_tracker.hpp"

namespace ball_tracker {


  // config
  #define SENSOR_ANGLE_RAD SENSOR_ANGLE * PI / 180
  #define ZERO_DIST (SENSOR_ANGLE_RAD == 0) ? 0 : SENSOR_HEIGHT / tan(SENSOR_ANGLE_RAD)


  // array of balls
  int ball_count = 0;
  Ball balls[MAX_BALLS];
  int ball_count_basic = 0;
  pros::vision_object_s_t balls_basic[MAX_BALLS];


  // vision sensor
  pros::vision_signature_s_t BALL_SIG_CONFIG = {1, {1, 0, 0}, 9.100, 893, 1905, 1399, -5643, -4965, -5304, 0, 0};
  pros::Vision vision_sensor(13);


  // initialize
  void init() {
    // vision_sensor.set_exposure(37);
    // vision_sensor.set_signature(BALL_SIG, &BALL_SIG_CONFIG);
  }


  // get basic ball data without fancy calculations
  void update_balls_basic() {
    ball_count_basic = vision_sensor.read_by_sig(0, BALL_SIG, MAX_BALLS, balls_basic);
  }


  // calculate distance from vision y coordinate
  float calc_ball_dist(float center_y) {
    return ZERO_DIST + DISTANCE_SCALAR * (VISION_IMAGE_HEIGHT/2 - center_y) / sin(SENSOR_ANGLE_RAD); // UNTESTED CALCULATION
  }


  // create ball object
  Ball create_ball(float vision_x, float vision_y, float width, float height) {
    Ball b;
    b.identified = true;
    b.vision_x = vision_x;
    b.vision_y = vision_y;
    b.robot_dist = calc_ball_dist(vision_y);
    b.robot_x = (VISION_IMAGE_WIDTH/2 - vision_x) / (VISION_IMAGE_HEIGHT - vision_y) * b.robot_dist; // UNTESTED CALCULATION
    return b;
  }


  // update ball list
  void update() {

    // "remove" all previously stored balls
    for (int i = 0; i < MAX_BALLS; i++) {
      balls[i].identified = false;
    }

    // find new balls
    pros::vision_object_s_t balls_raw[MAX_BALLS];
    ball_count = vision_sensor.read_by_sig(0, BALL_SIG, MAX_BALLS, balls_raw);

    if (ball_count == PROS_ERR || ball_count < 1) ball_count = 0;
    else {

      // convert to Ball structs
      Ball balls_unsorted[ball_count];
      for (int i = 0; i < ball_count; i++) {
        balls_unsorted[i] = create_ball(balls_raw[i].left_coord, balls_raw[i].top_coord, balls_raw[i].width, balls_raw[i].height);
      }

      // sort by distance and store in balls array
      for (int i = 0; i < ball_count; i++) {
        int min_index = 0;
        float min_dist = balls_unsorted[0].robot_dist;

        for (int j = 0; j < ball_count; j++) {
          if (balls_unsorted[min_index].identified == false || (balls_unsorted[j].identified && balls_unsorted[j].robot_dist < min_dist)) {
            min_index = j;
            min_dist = balls_unsorted[j].robot_dist;
          }
        }

        balls[i] = balls_unsorted[min_index];
        balls_unsorted[min_index].identified = false;
      }
    }
  }
}
