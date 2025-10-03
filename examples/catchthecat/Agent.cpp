#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D currentPos = frontier.front();

    if (checkEdge(w, currentPos)) { //make work with hexes
      break;
    }
    // remove the current from frontierset
    frontierSet.erase(currentPos);

    // mark current as visited
    visited.at(currentPos) = true;

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

bool Agent::checkEdge(World* w, Point2D currentPos) {
  if (abs(currentPos.x) == w->getWorldSideSize() || abs(currentPos.y) == w->getWorldSideSize()) {
    return true;
  }
  return false;
}

int Agent::heuristic(Point2D& cat, int sideSizeOver2) {
  return std::min(sideSizeOver2 - abs(cat.x), sideSizeOver2 - abs(cat.y));
}

std::vector<Point2D> Agent::getVisitables(World* w, unordered_map<Point2D, bool>& visited, Point2D currentPos) {
  std::vector<Point2D> visitables;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      Point2D temp = {currentPos.x + x, currentPos.y + y};

      if (currentPos.y % 2 == 0) {
        temp.x += 1;
      }

      if (!w->catCanMoveToPosition(temp)) { continue; }

      if (visited.at(temp)) { continue; }

      if (y != 0) {
        if (temp.x == 0 || temp.x == 1) {}
        else { continue; }
      }

      visitables.push_back(temp);
    }
  }

  return visitables;
}