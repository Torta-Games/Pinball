#include "ModuleScene.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading assets");
	bool ret = true;
	backgroundTexture = App->textures->Load("pinball/pinball_background.png");
	backgroundTexture2 = App->textures->Load("pinball/back.png");
	springTexture = App->textures->Load("pinball/spring.png");
	rotatingLightsTexture = App->textures->Load("pinball/circular_rotative_neon.png");
	glow100Texture = App->textures->Load("pinball/glow_100_points.png");
	glow200Texture = App->textures->Load("pinball/glow_200_points.png");
	glow500Texture = App->textures->Load("pinball/glow_500_points.png");
	glow1000Texture = App->textures->Load("pinball/glow_1000_points.png");
	glowLeftTexture = App->textures->Load("pinball/glow_abajo_izquierdo.png");
	glowRightTexture = App->textures->Load("pinball/glow_abajo_derecho.png");
	arrowLightsTexture = App->textures->Load("pinball/light_arrow.png");
	blueLightTexture = App->textures->Load("pinball/BlueLight/blue_light.png");

	arrowLights.PushBack({ 0,0,480,800 });
	arrowLights.PushBack({ 480,0,480,800 });
	arrowLights.PushBack({ 960,0,480,800 });
	arrowLights.PushBack({ 1440,0,480,800 });
	arrowLights.PushBack({ 1920,0,480,800 });
	arrowLights.speed = 0.1f;
	arrowLights.loop = true;

	blueLightAnim.PushBack({0,0,160,160});
	blueLightAnim.PushBack({160,0,160,160 });
	blueLightAnim.PushBack({320,0,160,160 });
	blueLightAnim.PushBack({480,0,160,160});
	blueLightAnim.PushBack({640,0,160,160});
	blueLightAnim.PushBack({800,0,160,160});
	blueLightAnim.PushBack({960,0,160,160});
	blueLightAnim.PushBack({1120,0,160,160});
	blueLightAnim.PushBack({1280,0,160,160});
	blueLightAnim.PushBack({1440,0,160,160});
	blueLightAnim.PushBack({1280,0,160,160});
	blueLightAnim.PushBack({1120,0,160,160});
	blueLightAnim.PushBack({960,0,160,160});
	blueLightAnim.PushBack({800,0,160,160});
	blueLightAnim.PushBack({640,0,160,160});
	blueLightAnim.PushBack({480,0,160,160});
	blueLightAnim.PushBack({320,0,160,160 });
	blueLightAnim.PushBack({160,0,160,160 });
	blueLightAnim.PushBack({0,0,160,160});
	blueLightAnim.speed=0.5f;
	blueLightAnim.loop = true;

	
	currentAnim = &arrowLights;
	currentAnimBlueLight = &blueLightAnim;

	springPosition = iPoint(461, 700);
	springBody = App->physics->CreateRectangle(springPosition.x, springPosition.y, 21, 16, b2_dynamicBody);
	springDown = App->physics->CreateRectangle(springPosition.x, springPosition.y + 40, 21, 20, b2_staticBody);
	b2DistanceJointDef distanceSpringJoint;
	distanceSpringJoint.bodyA = springBody->body;
	distanceSpringJoint.bodyB = springDown->body;
	distanceSpringJoint.localAnchorA.Set(0, 0);
	distanceSpringJoint.localAnchorB.Set(0, 0);
	distanceSpringJoint.length = 2.0f;
	distanceSpringJoint.collideConnected = false;
	distanceSpringJoint.frequencyHz = 8.0f;
	distanceSpringJoint.dampingRatio = 0.2f;
	b2PrismaticJoint* springJoint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&distanceSpringJoint);

	circle1000Body = App->physics->CreateCircle(199, 223, 22, b2_kinematicBody);
	circle1000Body->ctype = ColliderType::CIRCLE_1000;
	circle500Body = App->physics->CreateCircle(188, 302, 25, b2_kinematicBody);
	circle500Body->ctype = ColliderType::CIRCLE_500;
	circle200Body = App->physics->CreateCircle(282, 220, 25, b2_kinematicBody);
	circle200Body->ctype = ColliderType::CIRCLE_200;
	circle100Body = App->physics->CreateCircle(284, 315, 32, b2_kinematicBody);
	circle100Body->ctype = ColliderType::CIRCLE_100;

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");

	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	//b2Vec2 vel = springBody->body->GetLinearVelocity();

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		if (springForce < 360) {
			springForce += 10;
		}
		springBody->body->ApplyForceToCenter(b2Vec2(0, springForce), 1);
	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		springForce = 0;
	}

	rotation--;

	//springBody->body->SetLinearVelocity(vel);

	springPosition = iPoint(METERS_TO_PIXELS(springBody->body->GetPosition().x), METERS_TO_PIXELS(springBody->body->GetPosition().y));

	App->renderer->Blit(backgroundTexture, 0, 0);
	App->renderer->Blit(springTexture, springPosition.x-10, springPosition.y-8);
	App->renderer->Blit(rotatingLightsTexture, 125, 150, NULL, 1.0f, rotation);
	App->renderer->Blit(backgroundTexture2, 0, 0);

	if (circle100Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			circle100Colliding = false;
		}
		else App->renderer->Blit(glow100Texture, 0, 0);
	}
	if (circle200Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			circle200Colliding = false;
		}
		else App->renderer->Blit(glow200Texture, 0, 0);
	}
	if (circle500Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			circle500Colliding = false;
		}
		else App->renderer->Blit(glow500Texture, 0, 0);
	}
	if (circle1000Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			circle1000Colliding = false;
		}
		else App->renderer->Blit(glow1000Texture, 0, 0);
	}
	if (leftTriangleColliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			leftTriangleColliding = false;
		}
		else App->renderer->Blit(glowLeftTexture, 0, 0);
	}
	if (rightTriangleColliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			rightTriangleColliding = false;
		}
		else App->renderer->Blit(glowRightTexture, 0, 0);
	}


	currentAnimBlueLight->Update();
	currentAnim->Update();
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->renderer->Blit(arrowLightsTexture, 0, 0, &rect);
	SDL_Rect rect2 = currentAnimBlueLight->GetCurrentFrame();
	App->renderer->Blit(blueLightTexture, 10, 383, &rect2);


	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
