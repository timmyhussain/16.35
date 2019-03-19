#include <string.h>
#include "vehicle.h"
#include "controller.h"
#include <stdlib.h>
#include <math.h>

int test_controller();

int main (int argc, char ** argv) {
    // test controller functionality
    if (strcmp(argv[1],"fail") == 0) return -1; // bad!
    else if (strcmp(argv[1], "controller1") == 0) {
      int res = test_controller(1);
      return res;
    }
    else if (strcmp(argv[1], "controller2") == 0) {
      int res = test_controller(-1);
      return res;
    }
    else if (strcmp(argv[1], "controller3") == 0) {
      int res = test_controller(0);
      return res;
    }
    else return 0; // correct
}

int test_controller(int i) {

  double starting_pos[3] = {40.0, 40.0, 0};
  double ** offset = malloc(sizeof(double*));
  offset[0] = malloc(2*sizeof(double));
  offset[0][0] = i * -30;
  offset[0][1] = i * 1;

  vehicle * v = create_vehicle(starting_pos, 1, offset);

  control control = get_proportional_waypoint_control(v);

  switch (i) {
    case 1:
      if (control.angular_velocity == M_PI_4) return 0;
      return -1;
    case -1:
      if (control.angular_velocity < 0) return 0;
      return -1;
    case 0:
      if (control.angular_velocity == 0) return 0;
      return -1;
  }

  // if (control.angular_velocity > 0) {
  //   return 0;
  // }
  // else return -1;
}
