// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "PhysicsComponent.h"
#include "Actor.h"
#include "CircleComponent.h"
#include <vector>
#include <iostream>

PhysicsComponent::PhysicsComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mSpeed(Vector2(0,0))
{
	
}

void PhysicsComponent::Update(float deltaTime)
{
		
	float multiplier = 5;

	std::vector<Vector2>* forces = mOwner->getCurrentForces();
	Vector2 pos = mOwner->GetPosition();
	Vector2 grav = mOwner->getGravity();
	float mass = mOwner->getMass();
		
	std::cout << "Mass: " << mass << std::endl;
	std::cout << "Pos: (" << pos.x << ", " << pos.y << ")" << std::endl;
	std::cout << "Grav: (" << grav.x << ", " << grav.y << ")" << std::endl;

	// --- Calcula a força total aplicada neste frame
	Vector2 F = Vector2(0,0);
	while (!forces->empty()) 
	{
		F += forces->back(); // soma a força a F total
		forces->pop_back(); // remove a força que ja foi aplicada
	}
	std::cout << "Force: (" << F.x << ", " << F.y << ")" << std::endl;

	// --- Calcula a aceleracao total
	Vector2 a = Vector2(F.x/mass, F.y/mass);
	if (mSpeed.y < 250) // limita a velocidade maxima de descida
		a += grav;
	std::cout << "a: (" << a.x << ", " << a.y << ")" << std::endl;

	// --- Calcula a velocidade atual do ator
	mSpeed += a;

	std::cout << "v: (" << mSpeed.x << ", " << mSpeed.y << ")" << std::endl;

	// --- Gera a nova posicao
	// Consideramos gravidade na atualização da posição apenas para ela nao acumular velocidade o tempo todo
	pos += mSpeed * deltaTime * multiplier;
		
	std::cout << "new pos: (" << pos.x << ", " << pos.y << ")" << std::endl << std::endl;

	// --- Aplica os limites da tela
	if (pos.x < 0.0f) { pos.x = 0.0f; }
	else if (pos.x > 1024.0f) { pos.x = 1024.0f; }
	if (pos.y < 0.0f) { pos.y = 0.0f; }
	else if (pos.y > 650.0f) { pos.y = 650.0f; }

	mOwner->SetPosition(pos);
}
