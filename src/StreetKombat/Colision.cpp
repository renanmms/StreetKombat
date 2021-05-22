#include "Colision.h"

bool Colision::Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}

bool Colision::Intersect(const CircleComponent& a, const BoundingBoxComponent& b)
{
	float dify = a.GetCenter().y - b.GetCenter().y;
	dify = dify < 0 ? dify * -1 : dify;
	float difx = a.GetCenter().x - b.GetCenter().x;
	difx = difx < 0 ? difx * -1 : difx;
	bool colided = difx < a.GetRadius() + (b.GetWidth() / 2) && // Se esta dentro do bounding box em x
								 dify < a.GetRadius() + (b.GetHeight() / 2);   // Se esta dentro do bounding box em y

	return colided;
}