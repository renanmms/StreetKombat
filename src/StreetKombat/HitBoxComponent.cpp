#include "HitBoxComponent.h"
#include "Game.h"
#include "BoundingBoxComponent.h"
#include "CircleComponent.h"

HitBoxComponent::HitBoxComponent(Actor* owner)
	:mOwner(owner)
{
}

bool HitBoxComponent::Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}

bool HitBoxComponent::Intersect(const CircleComponent& a, const BoundingBoxComponent& b)
{
	float dify = a.GetCenter().y - b.GetCenter().y;
	dify = dify < 0 ? dify * -1 : dify;
	float difx = a.GetCenter().x - b.GetCenter().x;
	difx = difx < 0 ? difx * -1 : difx;
	bool do_intersect = difx < a.GetRadius() + (b.GetWidth() / 2) && // Se esta dentro do bounding box em x
								 dify < a.GetRadius() + (b.GetHeight() / 2);   // Se esta dentro do bounding box em y
	return do_intersect;
}

bool HitBoxComponent::Intersect(const BoundingBoxComponent& a, const BoundingBoxComponent& b)
{
	float dify = a.GetCenter().y - b.GetCenter().y;
	dify = dify < 0 ? dify * -1 : dify;
	float difx = a.GetCenter().x - b.GetCenter().x;
	difx = difx < 0 ? difx * -1 : difx;

	bool do_intersect = difx < a.GetWidth() / 2 + b.GetWidth() / 2 &&
											dify < a.GetHeight() / 2 + b.GetHeight() / 2;

	return do_intersect;
}
