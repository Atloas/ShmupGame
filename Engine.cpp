#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "Utils.h"
#include "IDs.h"
#include "Config.h"

Engine::Engine()
{
	//Initialize member variables, load models, etc.
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;
	aspectRatio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	playField = new Field(-PLAY_FIELD_WIDTH_2, PLAY_FIELD_WIDTH_2, -PLAY_FIELD_HEIGHT_2, PLAY_FIELD_HEIGHT_2);
	boundaryField = new Field(-BOUNDARY_FIELD_WIDTH_2, BOUNDARY_FIELD_WIDTH_2, -BOUNDARY_FIELD_HEIGHT_2, BOUNDARY_FIELD_HEIGHT_2);
	running = false;
	paused = true;
	timer = 0.0f;
	srand((unsigned int)time(NULL));

	loadModels(std::string("PLACEHOLDER"));

	context = new sf::ContextSettings(24, 0, 0, 3, 0);
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Projekt - Michal Zbrozek", sf::Style::Titlebar | sf::Style::Close, *context);
	window->setVerticalSyncEnabled(true);
	glViewport(0, 0, windowWidth, windowHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_TEXTURE_2D);
	GLfloat light0Pos[4] = {100.0f, -25.0f, 100.0f, 0.0f};
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(playField->getXMin(), playField->getXMax(), playField->getYMin(), playField->getYMax(), 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	player = new Player(sf::Vector2f(0.0f, -10.0f), sf::Vector2f(0.0f, 0.0f), playField);
	hurtFlash = new HurtFlash(0.2f);
	sea = new Sea(playField, 20, 40);
	actors.push_back(player);
}

Engine::~Engine()
{
	window->close();
	delete window;
	delete context;
	delete sea;
	for (unsigned int i = 0; i < actors.size(); i++)
	{
		delete actors.at(i);
	}
	for (unsigned int i = 0; i < effects.size(); i++)
	{
		delete effects.at(i);
	}
}

void Engine::run()
{
	std::vector<char> directionInputs;
	
	running = true;
	while (running)
	{
		frameTime = clock.restart().asSeconds();
		timer += frameTime;

		//Handle inputs
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Space)
			{
				if (paused)
					paused = false;
				player->setShooting(true);
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Space)
				player->setShooting(false);
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Escape)
				paused = !paused;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::R)
				restart();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			directionInputs.push_back('A');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			directionInputs.push_back('D');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			directionInputs.push_back('W');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			directionInputs.push_back('S');
			
		setPlayerDirection(directionInputs);
		directionInputs.clear();

		if (!paused)
		{
			//Check collisions
			for (unsigned int i = 0; i < actors.size(); i++)
			{
				Actor* actorA = actors.at(i);
				checkBoundaries(actorA);
				if (actors.at(i)->getCollideable())
				{
					for (unsigned int j = i + 1; j < actors.size(); j++)
					{
						Actor* actorB = actors.at(j);
						checkBoundaries(actorB);
						if (actorA->getCollideable() && checkCollision(actorA, actorB))
						{
							if (actorA == player || actorB == player)
								hurtFlash->setOpacity(0.2f);
							Effect *spawned1 = actorA->onCollision(actorB), *spawned2 = actorB->onCollision(actorA);
							if (spawned1 != nullptr)
							{
								effects.push_back(spawned1);
							}
							if (spawned2 != nullptr)
							{
								effects.push_back(spawned2);
							}
						}
					}
				}
			}

			//Allow objects to act and spawn bullets
			for (unsigned int i = 0; i < actors.size(); i++)
			{
				Actor* spawned = actors.at(i)->act(frameTime);
				if (spawned != nullptr)
					actors.push_back(spawned);
			}

			for (unsigned int i = 0; i < effects.size(); i++)
			{
				effects.at(i)->tick(frameTime);
			}

			sea->tick(frameTime);

			//Delete dead objects
			for (int i = actors.size() - 1; i >= 0; i--)
			{
				if (!actors.at(i)->getAlive())
					actors.erase(actors.begin() + i);
			}
			for (int i = effects.size() - 1; i >= 0; i--)
			{
				if (!effects.at(i)->getAlive())
					effects.erase(effects.begin() + i);
			}

			hurtFlash->tick(frameTime);

			spawnEnemies();
		}

		Utils::sortEffectVectorByHeight(effects);

		drawScene();
		window->display();
	}
}

void Engine::loadModels(std::string folderPath)
{
	//Replace with file reading or something?
	std::vector<sf::Vector3f> playerModel;
	playerModel.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	playerModel.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	playerModel.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	playerModel.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	playerModel.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	playerModel.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));

	std::vector<sf::Vector3f> enemyPlaneModel;
	enemyPlaneModel.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	enemyPlaneModel.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	enemyPlaneModel.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	enemyPlaneModel.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	enemyPlaneModel.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	enemyPlaneModel.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));

	std::vector<sf::Vector3f> playerBulletModel;
	playerBulletModel.push_back(sf::Vector3f(0.0f, 0.5f, 0.0f));
	playerBulletModel.push_back(sf::Vector3f(0.15f, 0.0f, 0.0f));
	playerBulletModel.push_back(sf::Vector3f(-0.15f, 0.0f, 0.0f));

	std::vector<sf::Vector3f> enemyBulletModel;
	enemyBulletModel.push_back(sf::Vector3f(0.0f, 0.5f, 0.0f));
	enemyBulletModel.push_back(sf::Vector3f(0.15f, 0.0f, 0.0f));
	enemyBulletModel.push_back(sf::Vector3f(-0.15f, 0.0f, 0.0f));

	std::vector<sf::Vector3f> enemyBoatModel;
	enemyBoatModel.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(-1.0f, 0.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(-1.0f, 0.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(-1.0f, -2.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(1.0f, -2.0f, 0.0f));
	enemyBoatModel.push_back(sf::Vector3f(-1.0f, -2.0f, 0.0f));

	std::vector<sf::Vector3f> enemyTurretModel;
	enemyTurretModel.push_back(sf::Vector3f(-0.25f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.25f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.25f, 1.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(-0.25f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(-0.25f, 1.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.25f, 1.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(-0.5f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.5f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(-0.5f, 0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	enemyTurretModel.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));

	Player::setModel(playerModel);
	EnemyPlane::setModel(enemyPlaneModel);
	PlayerBullet::setModel(playerBulletModel);
	EnemyBullet::setModel(enemyBulletModel);
	EnemyBoat::setModel(enemyBoatModel);
	EnemyTurret::setModel(enemyTurretModel);
}

void Engine::start()
{
	//Start game from menu
}

void Engine::restart()
{
	actors.clear();
	effects.clear();
	delete player;

	timer = 0.0f;

	player = new Player(sf::Vector2f(0.0f, -10.0f), sf::Vector2f(0.0f, 0.0f), playField);
	actors.push_back(player);
}

void Engine::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluLookAt(0.0f, -20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f);

	//TODO: Put all of the drawing functions and model definitions into a separate class, then just pass a pointer to the correct draw function to each game object on it's creation, then call it here as you were before
	sea->draw();

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors.at(i)->draw();
	}

	for (unsigned int i = 0; i < effects.size(); i++)
	{
		effects.at(i)->draw();
	}

	glDisable(GL_LIGHTING);

	hurtFlash->draw();

	if (paused)
	{
		drawPauseScreen();
	}
}

void Engine::drawPauseScreen()
{
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
	glVertex3f(-PLAY_FIELD_WIDTH_2, -PLAY_FIELD_HEIGHT_2, 99.0f);
	glVertex3f(PLAY_FIELD_WIDTH_2, -PLAY_FIELD_HEIGHT_2, 99.0f);
	glVertex3f(PLAY_FIELD_WIDTH_2, PLAY_FIELD_HEIGHT_2, 99.0f);
	glVertex3f(-PLAY_FIELD_WIDTH_2, PLAY_FIELD_HEIGHT_2, 99.0f);
	glEnd();
}

void Engine::setPlayerDirection(std::vector<char> directionInputs)
{
	sf::Vector2f direction;
	for (unsigned int i = 0; i < directionInputs.size(); i++)
	{
		switch (directionInputs.at(i))
		{
		case 'A':
			direction.x -= 1.0f;
			break;
		case 'D':
			direction.x += 1.0f;
			break;
		case 'W':
			direction.y += 1.0f;
			break;
		case 'S':
			direction.y -= 1.0f;
			break;
		}
	}

	direction = Utils::normalizeVector(direction);

	player->setDirection(direction);
}

bool Engine::checkCollision(Actor* inputA, Actor* inputB)
{
	if (inputA->getCollisionIdentifier() & inputB->getCollisionGroup() && inputA->getActive() && inputB->getActive())
	{
		float distance2 = pow(Utils::vectorLength2(inputA->getPosition() - inputB->getPosition()), 2);
		if (inputA->getCollisionRadius2() + inputB->getCollisionRadius2() > distance2)
			return true;
	}
	return false;
}

void Engine::spawnById(int id, sf::Vector2f position, sf::Vector2f direction)
{
	//unused
	Actor* created = nullptr;
	switch (id)
	{
	case ENEMY_PLANE_ID:
		created = new EnemyPlane(position, direction);
		break;
	case PLAYER_BULLET_ID:
		created = new PlayerBullet(position, direction);
		break;
	case ENEMY_BULLET_ID:
		created = new EnemyBullet(position, direction);
		break;
	case PLAYER_EXPLOSION_ID:
		break;
	case PLAYER_BULLET_EXPLOSION_ID:
		break;
	case ENEMY_PLANE_EXPLOSION_ID:
		break; 
	case ENEMY_BULLET_EXPLOSION_ID:
		break;
	}
	if (created != nullptr)
		actors.push_back(created);
}

void Engine::spawnEnemies()
{
	if (timer > 1.0f)
	{
		timer = 0.0f;
		float toSpawn = (float)rand()/(float)RAND_MAX;
		float randomX = (float)rand()/(float)RAND_MAX*(ENEMY_SPAWN_X_MAX - ENEMY_SPAWN_X_MIN) + ENEMY_SPAWN_X_MIN;
		if (toSpawn < 0.2f)
		{
			actors.push_back(new EnemyBoat(sf::Vector2f(randomX, 24.5f), sf::Vector2f(0.5f, -1.0f), player));
		}
		else
		{
			actors.push_back(new EnemyPlane(sf::Vector2f(randomX, 24.5f), sf::Vector2f(0.0f, -1.0f)));
		}
	}
}

void Engine::checkBoundaries(Actor* actor)
{
	if (!boundaryField->checkIfInside(actor->getPosition()))
	{
		actor->setAlive(false);
		return;
	}
	if (playField->checkIfInside(actor->getPosition()))
	{
		actor->setCollideable(true);
		actor->setActive(true);
	}
	else
	{
		actor->setActive(false);
	}
}
