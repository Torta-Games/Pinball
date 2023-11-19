#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	backgroundTexture = App->textures->Load("pinball/portada_pinball.png");
	//Disable();
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->player->Enable();
	App->scene->Enable();
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	buttonRect = { 81, 548, 320, 160 };

	SDL_GetMouseState(&mouse.x, &mouse.y);

	mouseOverButton = (mouse.x >= buttonRect.x && mouse.x <= buttonRect.x + buttonRect.w &&
					mouse.y >= buttonRect.y && mouse.y <= buttonRect.y + buttonRect.h);

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && mouseOverButton)
	{
		buttonClicked = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || buttonClicked)
	{
		Disable();
	}

	App->renderer->Blit(backgroundTexture, 0, 0);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
