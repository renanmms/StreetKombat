#include "SpecialComponent.h"
#include "Component.h"

SpecialComponent::SpecialComponent(Actor* owner, std::vector<int> activationSequence)
	:Component(owner,110)
	,mSequenceTimer(3.0f)
	,mActivationSequence(activationSequence)
{
}

void SpecialComponent::Update(float deltaTime) 
{
// ------ Update the sequence timer
	mSequenceTimer -= deltaTime;

}