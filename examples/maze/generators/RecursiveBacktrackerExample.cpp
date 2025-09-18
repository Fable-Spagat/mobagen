#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  if (stack.empty())
    stack.push_back(randomStartPoint(w));

  std::vector<Point2D> visitables = getVisitables(w, stack.back());

  if (!visitables.empty()) {
    int randomVisitable = rand() % visitables.size();

    //stack.back.
    //check if equal to up, down, etc.
    //Figure out how to delete wall (SetNorth(false))
    //go to visitable and do opposite

    stack.push_back(visitables[randomVisitable]);
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
  if (p.x > 0 && !visited[left.x][left.y])
    visitables.push_back(left);
  if (p.y < w->GetSize() - 1 && !visited[down.x][down.y])
    visitables.push_back(down);
  if (p.x < w->GetSize() - 1 && !visited[right.x][right.y])
    visitables.push_back(right);
  if (p.y > 0 && !visited[up.x][up.y])
    visitables.push_back(up);

  return visitables;
}
