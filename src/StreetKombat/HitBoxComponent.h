#pragma once
#include "Component.h"
#include "Actor.h"

class BoundingBoxComponent;
class CircleComponent;

class HitBoxComponent
{
// Construtor
public:
  HitBoxComponent(Actor* owner);
// Métodos
public:
  const Vector2& GetCenter() const { return mOwner->GetPosition(); }
  const Actor& GetOwner() const { return *mOwner; }
  bool Intersect(const CircleComponent& a, const CircleComponent& b);
  bool Intersect(const CircleComponent& a, const BoundingBoxComponent& b);
  bool Intersect(const BoundingBoxComponent& a, const BoundingBoxComponent& b);
// Atributos
private:
  Actor* mOwner;
};

