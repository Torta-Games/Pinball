#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void DestroyBall();

public:	
	p2List<PhysBody*> balls;
	SDL_Texture* ballTexture;

	bool isAlive = false;
	bool canDestroy = false;
	bool canTp1 = false;
	bool canTp2 = false;
	int ballCount = 4;

	int score = 0;

	int point, boing;

};