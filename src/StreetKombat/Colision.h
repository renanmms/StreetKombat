#pragma once
#include "CircleComponent.h"
#include "BoundingBoxComponent.h"

namespace Colision
{
	bool Intersect(const CircleComponent& a, const CircleComponent& b);
	bool Intersect(const CircleComponent& a, const BoundingBoxComponent& b);
};

