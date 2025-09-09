#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

  for (int i = 0; i < neighborhood.size(); i++) {
    Vector2f deltaVector, unitVector = Vector2f::zero();
    double vectorMag = 0.0;

    deltaVector = neighborhood[i]->getPosition() - boid->getPosition();
    vectorMag = deltaVector.getMagnitude();
    unitVector = deltaVector / vectorMag;

    if (vectorMag < desiredMinimalDistance) {
      separatingForce += (unitVector * weight) / vectorMag;
    }
  }

  separatingForce = Vector2f::normalized(separatingForce);

  separatingForce *= -25;

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
