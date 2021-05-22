#pragma once
#include "HitBoxComponent.h"
#include "Component.h"
#include "Math.h"

class BoundingBoxComponent :
    public HitBoxComponent
{
public:
  BoundingBoxComponent(Actor* owner, float width, float height);

  const float GetWidth() const 
  {
    return GetOwner().GetScale() * mWidth;
  }
  const float GetHeight() const 
  { 
    return GetOwner().GetScale() * mHeight;
  }
  bool Colide(const CircleComponent& other);
  bool Colide(const BoundingBoxComponent& other);
private:
  float mWidth;
  float mHeight;
};

