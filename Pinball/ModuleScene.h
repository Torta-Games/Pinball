#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleTextures.h"


class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

private:
	SDL_Texture* backgroundTexture;
	SDL_Texture* backgroundTexture2;
	SDL_Texture* springTexture;
	SDL_Texture* rotatingLightsTexture;
	SDL_Texture* glow100Texture;
	SDL_Texture* glow200Texture;
	SDL_Texture* glow500Texture;
	SDL_Texture* glow1000Texture;
	SDL_Texture* glowLeftTexture;
	SDL_Texture* glowRightTexture;

	PhysBody* springBody;
	iPoint springPosition;

	double rotation = 0;

};
