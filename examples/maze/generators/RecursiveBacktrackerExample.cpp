#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));
    w->SetNodeColor(stack.back(), Color::Red);

    if (!getVisitables(w, stack.back()).empty())
      return true;
  }
  else {
    visited[stack.back().x][stack.back().y] = true;

    std::vector<Point2D> visitables = getVisitables(w, stack.back());

    if (!visitables.empty()) {
      int randomVisitable = rand() % visitables.size();

      if (visitables[randomVisitable] == stack.back().Left()) {
        w->SetWest(stack.back(), false);

        w->SetEast(visitables[randomVisitable], false);
      }
      else if (visitables[randomVisitable] == stack.back().Up()) {
        w->SetNorth(stack.back(), false);

        w->SetSouth(visitables[randomVisitable], false);
      }
      else if (visitables[randomVisitable] == stack.back().Right()) {
        w->SetEast(stack.back(), false);

        w->SetWest(visitables[randomVisitable], false);
      }
      else {
        w->SetSouth(stack.back(), false);

        w->SetNorth(visitables[randomVisitable], false);
      }

      stack.push_back(visitables[randomVisitable]);

      visited[stack.back().x][stack.back().y] = true;
      w->SetNodeColor(stack.back(), Color::Red);

      return true;
    }

    w->SetNodeColor(stack.back(), Color::Black);
    stack.pop_back();
    return true;
  }

  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  Point2D up = p.Up();
  Point2D right = p.Right();
  Point2D down = p.Down();
  Point2D left = p.Left();

  // todo: implement this
  if (p.x >= -sideOver2)
    if (!visited[left.x][left.y])
      visitables.push_back(left);

  if (p.y <= sideOver2)
    if (!visited[down.x][down.y])
      visitables.push_back(down);

  if (p.x <= sideOver2)
    if (!visited[right.x][right.y])
      visitables.push_back(right);

  if (p.y >= -sideOver2)
    if (!visited[up.x][up.y])
      visitables.push_back(up);

  return visitables;
}
