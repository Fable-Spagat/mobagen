#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  bool checkEdge(World* w, Point2D currentPos);
  int heuristic(Point2D& cat, int sideSizeOver2);//must handle hexes. Find % 2 of size
  std::vector<Point2D> getVisitables(World* w, std::unordered_set<Point2D> queue, std::unordered_map<Point2D, bool>& visited, Point2D currentPos);
};

#endif  // AGENT_H
