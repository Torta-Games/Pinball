#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleScene.h"

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
	LOG("Loading player");
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && !isAlive && ballCount > 0)
	{
		DestroyBall();
		balls.add(App->physics->CreateCircle(462, 600, 10, b2_dynamicBody));
		balls.getLast()->data->listener = this;
		balls.getLast()->data->ctype = ColliderType::BALL;
		isAlive = true;
		ballCount--;
	}

	if (canDestroy)
	{
		canDestroy = false;
		DestroyBall();
	}

	if (canTp1)
	{
		canTp1 = false;
		balls.getLast()->data->body->SetTransform(b2Vec2(PIXEL_TO_METERS(390), PIXEL_TO_METERS(554)), 0);
	}

	if (canTp2)
	{
		canTp2 = false;
		balls.getLast()->data->body->SetTransform(b2Vec2(PIXEL_TO_METERS(60), PIXEL_TO_METERS(554)), 0);
	}

	p2List_item<PhysBody*>* c = balls.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ballTexture, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	//LOG("%i", score);
	return UPDATE_CONTINUE;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	b2Vec2 impulseDirection = bodyA->body->GetPosition() - bodyB->body->GetPosition();
	impulseDirection.Normalize();
	float impulseMagnitude = 1.0f;
	float impulseMagnitude2 = 0.5f;

	switch (bodyB->ctype)
	{
	case ColliderType::SENSOR:
		canDestroy = true;
		break;
	case ColliderType::TRIANGLE_LEFT:
		App->scene->leftTriangleColliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude2 * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::TRIANGLE_RIGHT:
		App->scene->rightTriangleColliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude2 * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::CIRCLE_1000:
		App->scene->circle1000Colliding = true;
		score += 1000;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::CIRCLE_500:
		App->scene->circle500Colliding = true;
		score += 500;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::CIRCLE_200:
		App->scene->circle200Colliding = true;
		score += 200;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::CIRCLE_100:
		App->scene->circle100Colliding = true;
		score += 100;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::CIRCLE_TP1:
		canTp1 = true;
		break;
	case ColliderType::CIRCLE_TP2:
		canTp2 = true;
		break;
	case ColliderType::BOING_1:
		App->scene->boing1Colliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::BOING_2:
		App->scene->boing2Colliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::BOING_3:
		App->scene->boing3Colliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	case ColliderType::BOING_4:
		App->scene->boing4Colliding = true;
		bodyA->body->ApplyLinearImpulse(impulseMagnitude * impulseDirection, bodyA->body->GetWorldCenter(), true);
		break;
	}
}

void ModulePlayer::DestroyBall()
{
    if (balls.count() > 0) {
        if (isAlive) isAlive = false;
        PhysBody* lastBall = balls.getLast()->data;
        if (lastBall != nullptr) {
            App->physics->world->DestroyBody(lastBall->body);
            balls.del(balls.getLast());
        }
    }
}