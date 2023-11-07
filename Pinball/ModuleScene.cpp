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
	springTexture = App->textures->Load("pinball/spring.png");
	springPosition = iPoint(461, 677);
	rectangles.add(App->physics->CreateRectangle(springPosition.x, springPosition.y, 21, 94, b2_kinematicBody));
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
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && springPosition.y <= 700) rectangles.getFirst()->data->body->SetLinearVelocity(b2Vec2(0,1));
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE && springPosition.y >= 677) rectangles.getFirst()->data->body->SetLinearVelocity(b2Vec2(0, -3)); 
	else rectangles.getFirst()->data->body->SetLinearVelocity(b2Vec2(0, 0));
	springPosition = iPoint(METERS_TO_PIXELS(rectangles.getFirst()->data->body->GetPosition().x), METERS_TO_PIXELS(rectangles.getFirst()->data->body->GetPosition().y));

	App->renderer->Blit(backgroundTexture, 0, 0);
	App->renderer->Blit(springTexture, springPosition.x-10, springPosition.y-47);
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
