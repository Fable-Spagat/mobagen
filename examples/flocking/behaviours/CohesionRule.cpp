#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = {0,0};

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  for (int i = 0; i < neighborhood.size(); i++) {
    if (neighborhood[i] != boid)
      cohesionForce += neighborhood[i]->getPosition();
  }

  if (neighborhood.size() - 1 == 0) {
    cohesionForce = {0,0};
  }
  else {
    cohesionForce /= neighborhood.size() - 1;
    cohesionForce /= boid->getDetectionRadius();
    cohesionForce -= boid->getPosition();
    cohesionForce *= weight;
  }
  // find center of mass

  return cohesionForce;
}