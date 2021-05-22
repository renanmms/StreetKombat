#pragma once
#include "Component.h"
class BoundingBoxComponent :
    public Component
{
public:
  const Vector2& GetCenter() const { return center; }
  const float GetWidth() const { return width; }
  const float GetHeight() const { return height; }

private:
  Vector2 center;
  float width;
  float height;
};

