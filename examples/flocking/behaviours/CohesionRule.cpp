#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = {0,0};

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  int count = 0;

  for (int i = 0; i < neighborhood.size(); i++) {
    cohesionForce += neighborhood[i]->getPosition();

    count++;
  }

  if (count == 0) {
    cohesionForce = {0,0};
  }
  else {
    cohesionForce /= count;
    cohesionForce -= boid->getPosition();
    cohesionForce = cohesionForce.normalized();
    cohesionForce *= weight;
  }
  // find center of mass

  return cohesionForce;
}