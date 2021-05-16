#pragma once
#include "Component.h"
#include "Game.h"
class SpecialComponent : public Component
{
// ------ Constructors / Destructors
public:
  SpecialComponent(Actor* owner, std::vector<int> activationSequence);

// ------ Attributes
private:
  float mSequenceTimer;
  std::vector<int> mActivationSequence;

// ------ Method override
public:
  void Update(float deltaTime) override;

};

