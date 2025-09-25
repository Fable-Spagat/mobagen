#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w) {
  // todo: code this
  // Get start point
  // If no neighbors are visitable find new start point
  // Else select random start point
  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));

    auto sideOver2 = w->GetSize() / 2;//Brute force fix
    if (stack.back().x == INT_MAX || stack.back().y == INT_MAX) {
      return false;
    }

    if (getVisitables(w, stack.back()).empty()) {
      w->SetNodeColor(stack.back(), Color::Black);
      completed[stack.back().x][stack.back().y] = true;
      stack.pop_back();
      return true;
    }
    if (!getVisitedNeighbors(w, stack.back()).empty()) {
      std::vector<Point2D> neighbors = getVisitedNeighbors(w, stack.back());

      if (neighbors[0] == stack.back().Left()) {
        w->SetWest(stack.back(), false);
      }
      else if (neighbors[0] == stack.back().Up()) {
        w->SetNorth(stack.back(), false);
      }
      else if (neighbors[0] == stack.back().Right()) {
        w->SetEast(stack.back(), false);
      }
      else if (neighbors[0] == stack.back().Down()) {
        w->SetSouth(stack.back(), false);
      }
    }

    if (!getVisitables(w, stack.back()).empty()) {
      visited[stack.back().x][stack.back().y] = true;
      w->SetNodeColor(stack.back(), Color::Red);

      return true;
    }
  }
  else {
    std::vector<Point2D> visitables = getVisitables(w, stack.back());

    if (!visitables.empty()) {
      int randomVisitable = rand() % visitables.size();

      if (visitables[randomVisitable] == stack.back().Left()) {
        w->SetWest(stack.back(), false);
      }
      else if (visitables[randomVisitable] == stack.back().Up()) {
        w->SetNorth(stack.back(), false);
      }
      else if (visitables[randomVisitable] == stack.back().Right()) {
        w->SetEast(stack.back(), false);
      }
      else if (visitables[randomVisitable] == stack.back().Down()) {
        w->SetSouth(stack.back(), false);
      }

      stack.push_back(visitables[randomVisitable]);

      visited[stack.back().x][stack.back().y] = true;
      w->SetNodeColor(stack.back(), Color::Red);

      return true;
    }

    w->SetNodeColor(stack.back(), Color::Black);
    completed[stack.back().x][stack.back().y] = true;
    stack.clear();
    return true;
  }

  return false;
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  completed.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
      completed[i][j] = false;
    }
  }
}
Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!completed[x][y]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: code this
  Point2D up = p.Up();
  Point2D right = p.Right();
  Point2D down = p.Down();
  Point2D left = p.Left();

  // todo: implement this
  if (p.x > -sideOver2)
    if (!visited[left.x][left.y])
      visitables.push_back(left);

  if (p.y < sideOver2)
    if (!visited[down.x][down.y])
      visitables.push_back(down);

  if (p.x < sideOver2)
    if (!visited[right.x][right.y])
      visitables.push_back(right);

  if (p.y > -sideOver2)
    if (!visited[up.x][up.y])
      visitables.push_back(up);

  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // todo: code this
  //Check for edges, if not on one add to neighbors
  Point2D up = p.Up();
  Point2D right = p.Right();
  Point2D down = p.Down();
  Point2D left = p.Left();

  // todo: implement this
  if (p.x > -sideOver2)
    if (visited[left.x][left.y])
      neighbors.push_back(left);

  if (p.y < sideOver2)
    if (visited[down.x][down.y])
      neighbors.push_back(down);

  if (p.x < sideOver2)
    if (visited[right.x][right.y])
      neighbors.push_back(right);

  if (p.y > -sideOver2)
    if (visited[up.x][up.y])
      neighbors.push_back(up);

  return neighbors;
}
