#pragma once

#include <GL\freeglut.h>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <vector>
#include <map>

#include "GameObject.h"
#include "Actor.h"
#include "Effect.h"
#include "Player.h"
#include "EnemyPlane.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "EnemyBoat.h"
#include "Sea.h"
#include "Field.h"
#include "HurtFlash.h"

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	void loadModels(std::string folderPath);

	void start();
	void restart();
	void drawScene();
	void drawPauseScreen();

	void setPlayerDirection(std::vector<char> directionInputs);

	bool checkCollision(Actor* inputA, Actor* inputB);

	void spawnById(int id, sf::Vector2f position, sf::Vector2f direction);

	void spawnEnemies();

	void checkBoundaries(Actor* actor);

	sf::Clock clock;
	float frameTime;
	float timer;

	sf::ContextSettings* context;
	sf::RenderWindow* window;
	int windowWidth, windowHeight;
	GLfloat aspectRatio;

	std::vector<Actor*> actors;
	std::vector<Effect*> effects;
	Player* player;
	Sea* sea;
	HurtFlash* hurtFlash;

	Field* playField;
	Field* boundaryField;

	bool running;
	bool paused;
};