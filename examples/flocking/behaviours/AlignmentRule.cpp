#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  int count = 0;

  for (int i = 0; i < neighborhood.size(); i++) {
    averageVelocity += neighborhood[i]->velocity;
    count++;
  }

  if (count == 0) {
    averageVelocity = {0,0};
  } 
  else {
    averageVelocity /= count;
    //averageVelocity = averageVelocity.normalized();
    averageVelocity *= weight;
  }

  return averageVelocity;
}