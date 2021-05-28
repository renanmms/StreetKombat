// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "Character.h"
#include <unordered_map>
#include <string>
#include <vector>

class Menu
{
public:
	Menu();
	bool Initialize();
	void RunLoop();
	void Shutdown();


};
