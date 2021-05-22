#include "SpecialComponent.h"
#include "Component.h"
#include "Special.h"

SpecialComponent::SpecialComponent(Character* owner, std::vector<int> activationSequence)
	:Component(owner,110)
	,owner(owner)
	,mCurrentState(0)
	,mLastKeyTime(0)
	,deltaTime(0)
	,mRechargeTime(0)
	,mActivationSequence(activationSequence)
{
}

void SpecialComponent::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void SpecialComponent::ProcessInput(const uint8_t* keyState)
{
	// ------ Atualiza tempo de recarga da habilidade
	mRechargeTime -= deltaTime;
	if (mRechargeTime > 0) return;
	// ------ Atualiza o tempo desde a ultima tecla
	mLastKeyTime += deltaTime;
	// ------ Verifica se passou do tempo minimo
	if (mLastKeyTime > 0.2f)
	{
		// ------ Se a tecla correta foi pressionada
		if (keyState[mActivationSequence[mCurrentState]])
		{
			// --- Atualiza o estado
			mCurrentState++;
			// --- Verifica se o jogador acertou a sequencia completa
			if (mCurrentState == mActivationSequence.size())
			{
				new Special(owner->GetGame(), owner);
				mRechargeTime = 1;
			}
			// --- Se o estado for final, volta pro inicio
			mCurrentState = mCurrentState % mActivationSequence.size();
			// --- Reset no tempo da ultima tecla apertada
			mLastKeyTime = 0;
		}
	}
	// ------ Verifica se passou do tempo maximo
	if (mLastKeyTime > 1.5f)
	{
		mCurrentState = 0;
	}
}
