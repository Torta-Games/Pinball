#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	ballTexture = App->textures->Load("pinball/ball.png");
	balls.add(App->physics->CreateCircle(385,780, 10, b2_staticBody));
	balls.add(App->physics->CreateCircle(410, 780, 10, b2_staticBody));
	balls.add(App->physics->CreateCircle(435, 780, 10, b2_staticBody));
	balls.add(App->physics->CreateCircle(460, 780, 10, b2_staticBody));
	balls.add(App->physics->CreateCircle(462, 600, 10, b2_dynamicBody));
	//balls.getLast()->data->listener = this;
	LOG("Loading player");
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	p2List_item<PhysBody*>* c = balls.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ballTexture, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}