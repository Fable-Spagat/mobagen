#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for (int x = 0; x < world.SideSize(); x++) {
    for (int y = 0; y < world.SideSize(); y++) {
      Point2D temp = {x, y};
      if (world.Get(temp)) {
        if (CountNeighbors(world, temp) < 2 || CountNeighbors(world, temp) > 3) {
          world.SetNext(temp, false);
        }
        else {
          world.SetNext(temp, true);
        }
      }
      else if (CountNeighbors(world, temp) == 3) {
        world.SetNext(temp, true);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int neighbors = 0;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0) {
        continue;
      }

      Point2D temp = {point.x + x, point.y + y};

      if (world.Get(temp)) {
        neighbors++;
      }
    }
  }
  return neighbors;
}
