#pragma once
#include "Component.h"
#include "Game.h"
class SpecialComponent : public Component
{
// ------ Constructors / Destructors
public:
  SpecialComponent(Character* owner, std::vector<int> activationSequence);

// ------ Attributes
private:
  Character* owner; // Ator dono deste especial
  int mCurrentState; // estado atual (inteiro apontando para a proxima tecla esperada)
  float deltaTime; // copia do delta time para controlar os tempos
  float mLastKeyTime; // tempo desde que a ultima tecla foi pressionada
  float mRechargeTime; // tempo para recarregar a habilidade
  std::vector<int> mActivationSequence;
  

// ------ Method override
public:
  void Update(float deltaTime) override;
  void ProcessInput(const uint8_t* keyState) override;

};

