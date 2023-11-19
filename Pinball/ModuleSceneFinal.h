#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneFinal : public Module
{
public:
	ModuleSceneFinal(Application* app, bool start_enabled = true);
	~ModuleSceneFinal();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	bool buttonClicked = false;
	bool mouseOverButton = false;
	iPoint mouse;
	SDL_Rect buttonRect;
	SDL_Texture* backgroundTexture;
	int score = 0;
	SDL_Rect scoreRect[10];
	SDL_Texture* numsTexture;
};
