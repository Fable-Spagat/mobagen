//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for (int x = 0; x < world.SideSize(); x++) {
    for (int y = 0; y < world.SideSize(); y++) {
      Point2D temp = {x, y};

      if (CountNeighbors(world, temp) == 2) {
        world.SetNext(temp, true);
      }
      else {
        world.SetNext(temp, false);
      }
    }
  }
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int neighbors = 0;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0) { continue; }

      Point2D temp = {point.x + x, point.y + y};
      int tempX = x;

      if (point.y % 2 == 0) {
        tempX += 1;
      }

      if (!world.Get(temp)) { continue; }

      if (y != 0) {
        if (tempX == 0 || tempX == 1) {}
        else { continue; }
      }

      neighbors++;
    }
  }

  return neighbors;
}
