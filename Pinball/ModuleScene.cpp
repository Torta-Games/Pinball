#include "ModuleScene.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include <iostream>
#include <string>

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	App->audio->Init();

	piston1Enabled = false;
	piston2Enabled = false;
	piston3Enabled = false;
	piston4Enabled = false;
	piston5Enabled = false;
	piston6Enabled = false;
	coins = false;

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
	rightFlipperTexture = App->textures->Load("pinball/flipper_right.png");
	leftFlipperTexture = App->textures->Load("pinball/flipper_left.png");
	blueLightTexture = App->textures->Load("pinball/BlueLight/blue_light.png");
	circleTexture = App->textures->Load("pinball/circles_points.png");
	numsTexture = App->textures->Load("pinball/nums.png");
	rightArrowTexture = App->textures->Load("pinball/right_arrow_lights.png");
	leftArrowTexture = App->textures->Load("pinball/left_arrow_lights.png");
	boing1Texture = App->textures->Load("pinball/glow_platform_upper_left.png");
	boing2Texture = App->textures->Load("pinball/glow_platform_upper_right.png");
	boing3Texture = App->textures->Load("pinball/glow_platform_down_left.png");
	boing4Texture = App->textures->Load("pinball/glow_platform_down_right.png");
	pistonTexture = App->textures->Load("pinball/piston.png");
	piston1LightTexture = App->textures->Load("pinball/light_piston_1_down.png");
	piston2LightTexture = App->textures->Load("pinball/light_piston_2_down.png");
	piston3LightTexture = App->textures->Load("pinball/light_piston_3_down.png");
	piston4LightTexture = App->textures->Load("pinball/light_piston_1_up.png");
	piston5LightTexture = App->textures->Load("pinball/light_piston_2_up.png");
	piston6LightTexture = App->textures->Load("pinball/light_piston_3_up.png");
	coinTexture = App->textures->Load("pinball/coin.png");

	flipperFx = App->audio->LoadFx("pinball/Audio/flipper.ogg");
	music = App->audio->LoadFx("pinball/Audio/music.ogg");
	combo = App->audio->LoadFx("pinball/Audio/combo.ogg");

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

	rightArrowAnim.PushBack({ 0,0,50,59});
	rightArrowAnim.PushBack({ 50,0,50,59 });
	rightArrowAnim.PushBack({ 100,0,50,59 });
	rightArrowAnim.PushBack({ 150,0,50,59 });
	rightArrowAnim.speed = 0.1f;
	rightArrowAnim.loop = true;

	leftArrowAnim.PushBack({ 0,0,60,60 });
	leftArrowAnim.PushBack({ 60,0,60,60 });
	leftArrowAnim.PushBack({ 120,0,60,60 });
	leftArrowAnim.PushBack({ 180,0,60,60 });
	leftArrowAnim.speed = 0.1f;
	leftArrowAnim.loop = true;

	coinAnim.PushBack({ 0,0,100,100 });
	coinAnim.PushBack({ 100,0,100,100 });
	coinAnim.PushBack({ 200,0,100,100 });
	coinAnim.PushBack({ 300,0,100,100 });
	coinAnim.PushBack({ 400,0,100,100 });
	coinAnim.PushBack({ 500,0,100,100 });
	coinAnim.speed = 0.2f;
	coinAnim.loop = true;
	coinPosition[0] = fPoint(50, 0);
	coinPosition[1] = fPoint(190, 0);
	coinPosition[2] = fPoint(340, 0);
	coinPosition[3] = fPoint(120, -150);
	coinPosition[4] = fPoint(280, -150);

	currentAnim = &arrowLights;
	currentAnimBlueLight = &blueLightAnim;
	currentAnimRightArrow = &rightArrowAnim;
	currentAnimLeftArrow = &leftArrowAnim;

	//RIGHT FLIPPER

	rightFlipperPosition = iPoint(313, 748);
	rightFlipperBody = App->physics->CreateRectangle(rightFlipperPosition.x, rightFlipperPosition.y, 70, 16, b2_dynamicBody);
	rightFlipperBody->ctype = ColliderType::RIGHT_FLIPPER;
	rightFlipperPoint = App->physics->CreateCircle(rightFlipperPosition.x, rightFlipperPosition.y, 2, b2_staticBody);

	b2RevoluteJointDef rightFlipperJointDef;
	rightFlipperJointDef.bodyA = rightFlipperBody->body;
	rightFlipperJointDef.bodyB = rightFlipperPoint->body;
	rightFlipperJointDef.referenceAngle = 0;
	rightFlipperJointDef.enableLimit = true;
	rightFlipperJointDef.lowerAngle = DEGTORAD * (-30);
	rightFlipperJointDef.upperAngle = DEGTORAD * (30);
	rightFlipperJointDef.localAnchorA.Set(PIXEL_TO_METERS(45), 0);
	rightFlipperJointDef.localAnchorB.Set(0, 0);
	b2RevoluteJoint* rightFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&rightFlipperJointDef);

	//LEFT FLIPPER
	leftFlipperPosition = iPoint(131, 745);
	leftFlipperBody = App->physics->CreateRectangle(leftFlipperPosition.x, leftFlipperPosition.y, 70, 16, b2_dynamicBody);
	leftFlipperBody->ctype = ColliderType::LEFT_FLIPPER;
	leftFlipperPoint = App->physics->CreateCircle(leftFlipperPosition.x, leftFlipperPosition.y, 2, b2_staticBody);

	b2RevoluteJointDef leftFlipperJointDef;
	leftFlipperJointDef.bodyA = leftFlipperBody->body;
	leftFlipperJointDef.bodyB = leftFlipperPoint->body;
	leftFlipperJointDef.referenceAngle = 0;
	leftFlipperJointDef.enableLimit = true;
	leftFlipperJointDef.lowerAngle = DEGTORAD * (-30);
	leftFlipperJointDef.upperAngle = DEGTORAD * (30);
	leftFlipperJointDef.localAnchorA.Set(PIXEL_TO_METERS(-45), 0);
	leftFlipperJointDef.localAnchorB.Set(0, 0);
	b2RevoluteJoint* leftFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&leftFlipperJointDef);

	//SPRING

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

	scoreFile.open("score.txt", ios::in);
	scoreFile >> highScore;
	cout << highScore;
	scoreFile.close();

	for (int i = 0; i < 10; i++)
	{
		scoreRect[i] = { 11 * i, 0, 8, 14 };
	}

	LoadMap();

	App->audio->PlayFx(music);

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");	
	App->textures->Unload(backgroundTexture);
	App->textures->Unload(backgroundTexture2);
	App->textures->Unload(springTexture);
	App->textures->Unload(rotatingLightsTexture);
	App->textures->Unload(glow100Texture);
	App->textures->Unload(glow200Texture);
	App->textures->Unload(glow500Texture);
	App->textures->Unload(glow1000Texture);
	App->textures->Unload(glowLeftTexture);
	App->textures->Unload(glowRightTexture);
	App->textures->Unload(arrowLightsTexture);
	App->textures->Unload(rightFlipperTexture);
	App->textures->Unload(leftFlipperTexture);
	App->textures->Unload(blueLightTexture);
	App->textures->Unload(circleTexture);
	App->textures->Unload(numsTexture);
	App->textures->Unload(rightArrowTexture);
	App->textures->Unload(leftArrowTexture);
	App->textures->Unload(boing1Texture);
	App->textures->Unload(boing2Texture);
	App->textures->Unload(boing3Texture);
	App->textures->Unload(boing4Texture);
	App->textures->Unload(pistonTexture);
	App->textures->Unload(piston1LightTexture);
	App->textures->Unload(piston2LightTexture);
	App->textures->Unload(piston3LightTexture);
	App->textures->Unload(piston4LightTexture);
	App->textures->Unload(piston5LightTexture);
	App->textures->Unload(piston6LightTexture);

	arrowLights.totalFrames = 0;
	blueLightAnim.totalFrames = 0;
	rightArrowAnim.totalFrames = 0;
	leftArrowAnim.totalFrames = 0;

	App->physics->world->DestroyBody(rightFlipperBody->body);
	App->physics->world->DestroyBody(rightFlipperPoint->body);
	App->physics->world->DestroyBody(leftFlipperBody->body);
	App->physics->world->DestroyBody(leftFlipperPoint->body);
	App->physics->world->DestroyBody(springBody->body);
	App->physics->world->DestroyBody(springDown->body);
	App->physics->world->DestroyBody(circle1000Body->body);
	App->physics->world->DestroyBody(circle500Body->body);
	App->physics->world->DestroyBody(circle200Body->body);
	App->physics->world->DestroyBody(circle100Body->body);
	App->physics->world->DestroyBody(Pinball->body);
	App->physics->world->DestroyBody(Abajo_Derecha->body);
	App->physics->world->DestroyBody(Abajo_Izquierda->body);
	App->physics->world->DestroyBody(Propulsor_1->body);
	App->physics->world->DestroyBody(Propulsor_2->body);
	App->physics->world->DestroyBody(Propulsor_3->body);
	App->physics->world->DestroyBody(Propulsor_4->body);
	App->physics->world->DestroyBody(Propulsor_5->body);
	App->physics->world->DestroyBody(Propulsor_6->body);
	App->physics->world->DestroyBody(Palo_1->body);
	App->physics->world->DestroyBody(Palo_2->body);
	App->physics->world->DestroyBody(Palo_3->body);
	App->physics->world->DestroyBody(Palo_4->body);
	App->physics->world->DestroyBody(Boing_1->body);
	App->physics->world->DestroyBody(Boing_2->body);
	App->physics->world->DestroyBody(Boing_3->body);
	App->physics->world->DestroyBody(Boing_4->body);
	App->physics->world->DestroyBody(circulo1->body);
	App->physics->world->DestroyBody(circulo2->body);
	App->physics->world->DestroyBody(circulo3->body);
	App->physics->world->DestroyBody(circulo10k->body);
	App->physics->world->DestroyBody(circulo5k->body);
	App->physics->world->DestroyBody(circulo1k->body);
	App->physics->world->DestroyBody(circulo100L->body);
	App->physics->world->DestroyBody(circulo100R->body);

	App->audio->CleanUp();

	return true;
}

void ModuleScene::LoadMap()
{
	Pinball = (App->physics->CreateChain(0, 0, pinball, 603, b2BodyType::b2_staticBody));

	Abajo_Derecha = (App->physics->CreateChain(0, 0, abajo_derecha, 36, b2BodyType::b2_staticBody));
	Abajo_Derecha->listener = this;
	Abajo_Derecha->ctype = ColliderType::TRIANGLE_RIGHT;

	Abajo_Izquierda = (App->physics->CreateChain(0, 0, abajo_izquierda, 34, b2BodyType::b2_staticBody));
	Abajo_Izquierda->listener = this;
	Abajo_Izquierda->ctype = ColliderType::TRIANGLE_LEFT;

	Propulsor_1 = (App->physics->CreateChain(0, 0, propulsor1, 10, b2BodyType::b2_staticBody));
	Propulsor_1->ctype = ColliderType::PISTON4;
	Propulsor_2 = (App->physics->CreateChain(0, 0, propulsor2, 12, b2BodyType::b2_staticBody));
	Propulsor_2->ctype = ColliderType::PISTON5;
	Propulsor_3 = (App->physics->CreateChain(0, 0, propulsor3, 12, b2BodyType::b2_staticBody));
	Propulsor_3->ctype = ColliderType::PISTON6;

	Propulsor_4 = (App->physics->CreateChain(0, 0, propulsor4, 10, b2BodyType::b2_staticBody));
	Propulsor_4->ctype = ColliderType::PISTON1;
	Propulsor_5 = (App->physics->CreateChain(0, 0, propulsor5, 10, b2BodyType::b2_staticBody));
	Propulsor_5->ctype = ColliderType::PISTON2;
	Propulsor_6 = (App->physics->CreateChain(0, 0, propulsor6, 10, b2BodyType::b2_staticBody));
	Propulsor_6->ctype = ColliderType::PISTON3;

	Palo_1 = (App->physics->CreateChain(0, 0, palo1, 24, b2BodyType::b2_staticBody));
	Palo_2 = (App->physics->CreateChain(0, 0, palo2, 26, b2BodyType::b2_staticBody));
	Palo_3 = (App->physics->CreateChain(0, 0, palo3, 26, b2BodyType::b2_staticBody));
	Palo_4 = (App->physics->CreateChain(0, 0, palo4, 28, b2BodyType::b2_staticBody));

	cordsBoing1 = iPoint(27, 146);
	cordsBoing2 = iPoint(255, 119);
	cordsBoing3 = iPoint(77, 517);
	cordsBoing4 = iPoint(355, 539);
	Boing_1 = (App->physics->CreateRectangle(cordsBoing1.x, cordsBoing1.y, 51, 7, b2BodyType::b2_staticBody));
	Boing_1->body->SetTransform(Boing_1->body->GetPosition(), DEGTORAD * 108);
	//Boing_1 = (App->physics->CreateChain(0, 0, boing1, 14, b2BodyType::b2_staticBody)); //Arriba Izquierda
	Boing_2 = (App->physics->CreateRectangle(cordsBoing2.x, cordsBoing2.y, 22, 7, b2BodyType::b2_staticBody));
	Boing_2->body->SetTransform(Boing_2->body->GetPosition(), DEGTORAD * 93);
	//Boing_2 = (App->physics->CreateChain(0, 0, boing2, 10, b2BodyType::b2_staticBody)); //Arriba derecha peque�o
	Boing_3 = (App->physics->CreateRectangle(cordsBoing3.x, cordsBoing3.y, 55, 5, b2BodyType::b2_staticBody));
	Boing_3->body->SetTransform(Boing_3->body->GetPosition(), DEGTORAD * -120);
	//Boing_3 = (App->physics->CreateChain(0, 0, boing3, 14, b2BodyType::b2_staticBody)); //Abajo Izquierda
	Boing_4 = (App->physics->CreateRectangle(cordsBoing4.x + 17, cordsBoing4.y - 25, 55, 5, b2BodyType::b2_staticBody));
	Boing_4->body->SetTransform(Boing_4->body->GetPosition(), DEGTORAD * 120);
	//Boing_4 = (App->physics->CreateChain(0, 0, boing4, 14, b2BodyType::b2_staticBody)); //Abajo Derecha

	Boing_1->ctype = ColliderType::BOING_1;
	Boing_2->ctype = ColliderType::BOING_2;
	Boing_3->ctype = ColliderType::BOING_3;
	Boing_4->ctype = ColliderType::BOING_4;

	circulo1 = (App->physics->CreateCircle(19, 334, 7, b2BodyType::b2_staticBody));
	circulo1->body->GetFixtureList()->SetSensor(true);
	circulo1->ctype = ColliderType::CIRCLE_TP1;
	circulo2 = (App->physics->CreateCircle(161, 99, 7, b2BodyType::b2_staticBody));
	circulo2->body->GetFixtureList()->SetSensor(true);
	circulo2->ctype = ColliderType::CIRCLE_TP2;

	circulo3 = (App->physics->CreateCircle(110, 337, 15, b2BodyType::b2_staticBody));
	circulo3->body->GetFixtureList()->SetSensor(true);
	circulo3->ctype = ColliderType::COINS;

	circulo10k = (App->physics->CreateCircle(19, 256, 15, b2BodyType::b2_staticBody));
	circulo10k->body->GetFixtureList()->SetSensor(true);
	circulo10k->ctype = ColliderType::CIRCLE_10k;

	circulo5k = (App->physics->CreateCircle(54, 242, 15, b2BodyType::b2_staticBody));
	circulo5k->body->GetFixtureList()->SetSensor(true);
	circulo5k->ctype = ColliderType::CIRCLE_5k;

	circulo1k = (App->physics->CreateCircle(90, 228, 15, b2BodyType::b2_staticBody));
	circulo1k->body->GetFixtureList()->SetSensor(true);
	circulo1k->ctype = ColliderType::CIRCLE_1k;

	circulo100L = (App->physics->CreateCircle(60, 660, 10, b2BodyType::b2_staticBody));
	circulo100L->body->GetFixtureList()->SetSensor(true);
	circulo100L->ctype = ColliderType::CIRCLE_100L;

	circulo100R = (App->physics->CreateCircle(388, 660, 10, b2BodyType::b2_staticBody));
	circulo100R->body->GetFixtureList()->SetSensor(true);
	circulo100R->ctype = ColliderType::CIRCLE_100R;

	boxes.add(App->physics->CreateRectangleSensor(230, 800, 220, 2));
	boxes.getLast()->data->listener = this;
	boxes.getLast()->data->ctype = ColliderType::SENSOR;

}

// Update: draw background
update_status ModuleScene::Update()
{
	if (App->player->score > highScore)
	{
		highScore = App->player->score;
		scoreFile.open("score.txt", ios::out);
		scoreFile.seekp(0);
		scoreFile << highScore;
		scoreFile.close();
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (springForce < 360) {
			springForce += 10;
		}
		springBody->body->ApplyForceToCenter(b2Vec2(0, springForce), 1);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		springForce = 0;
	}

	//control the flipper using right arrow key
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		rightFlipperActivated = true;
		rightFlipperBody->body->ApplyForceToCenter(b2Vec2(0, -1000), true);
		App->audio->PlayFx(flipperFx);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		leftFlipperActivated = true;
		leftFlipperBody->body->ApplyForceToCenter(b2Vec2(0, -1000), true);
		App->audio->PlayFx(flipperFx);
	}

	rotation--;

	springPosition = iPoint(METERS_TO_PIXELS(springBody->body->GetPosition().x), METERS_TO_PIXELS(springBody->body->GetPosition().y));
	rightFlipperPosition = iPoint(METERS_TO_PIXELS(rightFlipperBody->body->GetPosition().x), METERS_TO_PIXELS(rightFlipperBody->body->GetPosition().y));
	leftFlipperPosition = iPoint(METERS_TO_PIXELS(leftFlipperBody->body->GetPosition().x), METERS_TO_PIXELS(leftFlipperBody->body->GetPosition().y));

	App->renderer->Blit(backgroundTexture, 0, 0);
	App->renderer->Blit(springTexture, springPosition.x-10, springPosition.y-8);
	App->renderer->Blit(rotatingLightsTexture, 125, 150, NULL, 1.0f, rotation);
	App->renderer->Blit(backgroundTexture2, 0, 0);
	App->renderer->Blit(circleTexture, 0, 0);

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

	if (boing1Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			boing1Colliding = false;
		}
		else App->renderer->Blit(boing1Texture, 0, 0);
	}
	if (boing2Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			boing2Colliding = false;
		}
		else App->renderer->Blit(boing2Texture, 0, 0);
	}
	if (boing3Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			boing3Colliding = false;
		}
		else App->renderer->Blit(boing3Texture, 0, 0);
	}
	if (boing4Colliding)
	{
		if (timer == 0) timer = SDL_GetTicks();

		if (SDL_GetTicks() - timer >= 200)
		{
			timer = 0;
			boing4Colliding = false;
		}
		else App->renderer->Blit(boing4Texture, 0, 0);
	}


	App->renderer->Blit(rightFlipperTexture, rightFlipperPosition.x - 32, rightFlipperPosition.y - 32, NULL, 0, rightFlipperBody->GetRotation() + 30, 32, 32);
	App->renderer->Blit(leftFlipperTexture, leftFlipperPosition.x - 50, leftFlipperPosition.y - 30, NULL, 0, leftFlipperBody->GetRotation() - 30, 50, 30);

	currentAnimBlueLight->Update();

	currentAnim->Update();
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->renderer->Blit(arrowLightsTexture, 0, 0, &rect);
	SDL_Rect rect2 = currentAnimBlueLight->GetCurrentFrame();
	App->renderer->Blit(blueLightTexture, 10, 383, &rect2);

	currentAnimRightArrow->Update();
	SDL_Rect rect3 = currentAnimRightArrow->GetCurrentFrame();
	App->renderer->Blit(rightArrowTexture, 376, 393, &rect3);

	currentAnimLeftArrow->Update();
	SDL_Rect rect4 = currentAnimLeftArrow->GetCurrentFrame();
	App->renderer->Blit(leftArrowTexture, 131, 378, &rect4);



	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		piston1Enabled = !piston1Enabled;
		piston2Enabled = !piston2Enabled;
		piston3Enabled = !piston3Enabled;
		piston4Enabled = !piston4Enabled;
		piston5Enabled = !piston5Enabled;
		piston6Enabled = !piston6Enabled;
	}

	if (piston1Enabled && piston2Enabled && piston3Enabled)
	{
		App->player->score += 10000;
		piston1Enabled = false;
		piston2Enabled = false;
		piston3Enabled = false;
		App->audio->PlayFx(combo);
	}

	if (piston4Enabled && piston5Enabled && piston6Enabled)
	{
		App->player->score += 5000;
		piston4Enabled = false;
		piston5Enabled = false;
		piston6Enabled = false;
		App->audio->PlayFx(combo);
	}

	if (!piston1Enabled)
	{
		App->renderer->Blit(pistonTexture, 14, 381, &pistonDisabledRect);
		App->renderer->Blit(piston1LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 15, 384, &pistonEnabledRect);
		App->renderer->Blit(piston1LightTexture, 0, 0, &pistonLightEnabledRect);
	}

	if (!piston2Enabled)
	{
		App->renderer->Blit(pistonTexture, 57, 387, &pistonDisabledRect);
		App->renderer->Blit(piston2LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 58, 389, &pistonEnabledRect);
		App->renderer->Blit(piston2LightTexture, 0, 0, &pistonLightEnabledRect);
	}

	if (!piston3Enabled)
	{
		App->renderer->Blit(pistonTexture, 98, 389, &pistonDisabledRect);
		App->renderer->Blit(piston3LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 99, 391, &pistonEnabledRect);
		App->renderer->Blit(piston3LightTexture, 0, 0, &pistonLightEnabledRect);
	}

	if (!piston4Enabled)
	{
		App->renderer->Blit(pistonTexture, 129, 158, &pistonDisabledRect, 0, -20);
		App->renderer->Blit(piston4LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 131, 160, &pistonEnabledRect, 0, -20);//////
		App->renderer->Blit(piston4LightTexture, 0, 0, &pistonLightEnabledRect);
	}

	if (!piston5Enabled)
	{
		App->renderer->Blit(pistonTexture, 158, 134, &pistonDisabledRect, 0, -5);
		App->renderer->Blit(piston5LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 160, 138, &pistonEnabledRect, 0, -5);
		App->renderer->Blit(piston5LightTexture, 0, 0, &pistonLightEnabledRect);
	}

	if (!piston6Enabled)
	{
		App->renderer->Blit(pistonTexture, 190, 121, &pistonDisabledRect, 0, 16);
		App->renderer->Blit(piston6LightTexture, 0, 0, &pistonLightDisabledRect);
	}
	else
	{
		App->renderer->Blit(pistonTexture, 190, 124, &pistonEnabledRect, 0, 16);
		App->renderer->Blit(piston6LightTexture, 0, 0, &pistonLightEnabledRect);
	}


	string scoreString = to_string(App->player->score);
	int scoreXPos = 130 - (scoreString.size() * 8);

	for (unsigned int i = 0; i < scoreString.size(); i++)
	{
		int digit = scoreString[i] - '0';

		App->renderer->Blit(numsTexture, scoreXPos + (i * 10), 16, &scoreRect[digit], 0.0f);
	}

	string highScoreString = to_string(highScore);
	int highScoreXPos = 455 - (highScoreString.size() * 8);

	for (unsigned int i = 0; i < highScoreString.size(); i++)
	{
		int digit = highScoreString[i] - '0';

		App->renderer->Blit(numsTexture, highScoreXPos + (i * 10), 40, &scoreRect[digit], 0.0f);
	}

	if (coins && coinPosition[0].y<1000)
	{
		coinPosition[0].y += 5;
		coinPosition[1].y += 5;
		coinPosition[2].y += 5;
		coinPosition[3].y += 5;
		coinPosition[4].y += 5;
		coinAnim.Update();
		SDL_Rect rect5 = coinAnim.GetCurrentFrame();
		App->renderer->Blit(coinTexture, coinPosition[0].x, coinPosition[0].y, &rect5);
		App->renderer->Blit(coinTexture, coinPosition[1].x, coinPosition[1].y, &rect5);
		App->renderer->Blit(coinTexture, coinPosition[2].x, coinPosition[2].y, &rect5);
		App->renderer->Blit(coinTexture, coinPosition[3].x, coinPosition[3].y, &rect5);
		App->renderer->Blit(coinTexture, coinPosition[4].x, coinPosition[4].y, &rect5);
		if (coinPosition[0].y>999)
		{
			coins = false;
			coinPosition[0] = fPoint(50, 0);
			coinPosition[1] = fPoint(190, 0);
			coinPosition[2] = fPoint(340, 0);
			coinPosition[3] = fPoint(120, -150);
			coinPosition[4] = fPoint(280, -150);
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
