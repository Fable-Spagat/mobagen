#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  bool checkEdge(World* w, Point2D currentPos);
  int manhattanDistance(Point2D& cat, int sideSizeOver2);//must handle hexes. Find % 2 of size
};

#endif  // AGENT_H
