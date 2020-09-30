#pragma once
#include "Actor.h"
#include "Weapon.h"

#include <SFML\System\Vector2.hpp>

enum ENEMY_TYPE
{
	PLANE,
	BOAT
};

class Enemy :
	public Actor
{
public:
	Enemy(sf::Vector3f position, sf::Vector3f direction, ENEMY_TYPE type, std::vector<sf::Vector3f>* model);
	virtual ~Enemy();

	void act(float frameTime);
	void onCollision(Actor& other);
	void draw();

private:
	sf::Vector2<float> direction;
	ENEMY_TYPE type;
	void (*behaviour)(Enemy& subject);

	//TODO: Model& model;
	std::vector<sf::Vector3f>& model;
	std::vector<Weapon> weapons;

};

//TODO: replace with EnemyFactory
class EnemyBuilder
{
public:
	EnemyBuilder();

	EnemyBuilder& setPosition(sf::Vector3f position);
	EnemyBuilder& setDirection(sf::Vector3f direction);
	EnemyBuilder& setType(ENEMY_TYPE type);
	EnemyBuilder& setModel(std::vector<sf::Vector3f>* model);

	Enemy build();

private:
	sf::Vector3f position;
	sf::Vector3f direction;
	ENEMY_TYPE type;
	std::vector<sf::Vector3f>* model;
};