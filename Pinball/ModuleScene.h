#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "Animation.h"


class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


	bool leftTriangleColliding = false;
	bool rightTriangleColliding = false;
	bool circle1000Colliding = false;
	bool circle500Colliding = false;
	bool circle200Colliding = false;
	bool circle100Colliding = false;
	float timer = 0;

	bool rightFlipperActivated = false;
	bool leftFlipperActivated = false;

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
	SDL_Texture* rightFlipperTexture;
	SDL_Texture* leftFlipperTexture;

	PhysBody* rightFlipperBody;
	PhysBody* rightFlipperPoint;
	PhysBody* leftFlipperBody;
	PhysBody* leftFlipperPoint;

	PhysBody* springBody;
	PhysBody* springDown;
	PhysBody* circle1000Body;
	PhysBody* circle500Body;
	PhysBody* circle200Body;
	PhysBody* circle100Body;
	iPoint springPosition;
	iPoint rightFlipperPosition;
	iPoint leftFlipperPosition;

	Animation* currentAnim;
	Animation arrowLights;
	SDL_Texture* arrowLightsTexture;


	Animation* currentAnimBlueLight;
	Animation blueLightAnim;
	SDL_Texture* blueLightTexture;

	SDL_Texture* circleTexture;

	Animation* currentAnimRightArrow;
	Animation rightArrowAnim;
	SDL_Texture* rightArrowTexture;

	Animation* currentAnimLeftArrow;
	Animation leftArrowAnim;
	SDL_Texture* leftArrowTexture;

	int springForce = 0;

	double rotation = 0;

	int x, y = 0;
};
