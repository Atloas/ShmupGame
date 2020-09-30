#include "Enemy.h"



Enemy::Enemy(sf::Vector3f position, sf::Vector3f direction, ENEMY_TYPE type, std::vector<sf::Vector3f>* model): Actor(position, direction), model(*model)
{
	this->type = type;
}


Enemy::~Enemy()
{
}

void Enemy::act(float frameTime)
{
	behaviour(*this);
}

void Enemy::onCollision(Actor & other)
{
	if (other.getId() == PLAYER_ID)
		health = 0;

	//Check other party's collision damage
	health--;
	if (health > 0)
		return;
	else
	{
		setActive(false);
		setAlive(false);
		//Put an event on the queue that states this enemy died, with enemy type and coordinates
		return;
	}
}

void Enemy::draw()
{

}

EnemyBuilder::EnemyBuilder()
{

}

EnemyBuilder& EnemyBuilder::setPosition(sf::Vector3f position)
{
	this->position = position;
	return *this;
}

EnemyBuilder& EnemyBuilder::setDirection(sf::Vector3f direction)
{
	this->direction = direction;
	return *this;
}

EnemyBuilder& EnemyBuilder::setType(ENEMY_TYPE type)
{
	this->type = type;
	return *this;
}

EnemyBuilder& EnemyBuilder::setModel(std::vector<sf::Vector3f>* model)
{
	this->model = model;
	return *this;
}

Enemy EnemyBuilder::build()
{
	return Enemy(position, direction, type, model);
}