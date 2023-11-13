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
	springPosition = iPoint(461, 676);
	springBody = App->physics->CreateRectangle(springPosition.x, springPosition.y, 21, 94, b2_kinematicBody);
	circle1000Body = App->physics->CreateCircle(199, 223, 22, b2_kinematicBody);
	circle1000Body->ctype = ColliderType::CIRCLE_1000;
	circle500Body = App->physics->CreateCircle(188, 302, 25, b2_kinematicBody);
	circle500Body->ctype = ColliderType::CIRCLE_500;
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
	b2Vec2 vel = springBody->body->GetLinearVelocity();

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && springPosition.y < 700)
	{
		vel.y++;
	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE && springPosition.y > 676)
	{
		vel.y-=2;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && springPosition.y >= 700 
		|| App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE && springPosition.y <= 676)
	{
		vel.SetZero();
	}

	rotation--;

	springBody->body->SetLinearVelocity(vel);

	springPosition = iPoint(METERS_TO_PIXELS(springBody->body->GetPosition().x), METERS_TO_PIXELS(springBody->body->GetPosition().y));

	App->renderer->Blit(backgroundTexture, 0, 0);
	App->renderer->Blit(springTexture, springPosition.x-10, springPosition.y-47);
	App->renderer->Blit(rotatingLightsTexture, 125, 150, NULL, 1.0f, rotation);
	//App->renderer->Blit(backgroundTexture2, 0, 0);
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) App->renderer->Blit(glow100Texture, 0, 0);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) App->renderer->Blit(glow200Texture, 0, 0);
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

	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
