#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);

  if (!path.empty()) {
    return path.back();
  }

  while (true) {
    auto rand = Random::Range(0, 5); //moves onto blocked tile
    auto pos = world->getCat();
    switch (rand) {
      case 0:
        if (!world->getContent(World::NE(pos)))
          return  World::NE(pos);
      case 1:
        if (!world->getContent(World::NW(pos)))
        return World::NW(pos);
      case 2:
        if (!world->getContent(World::E(pos)))
        return World::E(pos);
      case 3:
        if (!world->getContent(World::W(pos)))
        return World::W(pos);
      case 4:
        if (!world->getContent(World::SW(pos)))
        return World::SW(pos);
      case 5:
        if (!world->getContent(World::SE(pos)))
        return World::SE(pos);
    }
  }
}
