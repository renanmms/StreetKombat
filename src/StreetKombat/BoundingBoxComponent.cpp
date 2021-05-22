#include "BoundingBoxComponent.h"

BoundingBoxComponent::BoundingBoxComponent(Actor* owner, float width, float height)
	:HitBoxComponent(owner)
	,mWidth(width)
	,mHeight(height)
{
}

bool BoundingBoxComponent::Colide(const CircleComponent& other)
{
	return Intersect(other, *this);
}

bool BoundingBoxComponent::Colide(const BoundingBoxComponent& other)
{
	return Intersect(*this, other);
}
