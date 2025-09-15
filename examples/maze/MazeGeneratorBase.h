#ifndef MAZEGENERATORBASE_H
#define MAZEGENERATORBASE_H

#include <string>
#include <vector>

class World;

enum class Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

struct maze {
  size_t rows, cols;
  std::vector<bool> horizontals, verticals;

  bool GetWall(size_t x, size_t y, Direction dir) { //linearized
    switch (dir) {
      case Direction::NORTH:
        return horizontals[y*cols + x];
      case Direction::EAST:
        return verticals[y*cols + (x+1)];
      case Direction::SOUTH:
        return horizontals[(y+1)*cols + x];
      case Direction::WEST:
        return verticals[y*cols + x];
    }
  }
};

class MazeGeneratorBase {
public:
  MazeGeneratorBase() = default;
  virtual std::string GetName() = 0;
  // Step should return true if it made changes in the world
  virtual bool Step(World* world) = 0;
  // Clears and resets all data from the generator
  virtual void Clear(World* world) = 0;
  virtual ~MazeGeneratorBase() = default;
};

#endif  // MAZEGENERATORBASE_H
