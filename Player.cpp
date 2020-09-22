#include "Player.h"

#include <SFML\OpenGL.hpp>

#include "PlayerBullet.h"
#include "Explosion.h"
#include "Utils.h"

#include <iostream>

std::vector<sf::Vector3f> Player::model;

Player::Player(sf::Vector2f position, sf::Vector2f direction, Field* playField) : Actor(position, direction)
{
	id = PLAYER_ID;

	this->height = 97.0f;
	this->playField = playField;

	speed = 10.0f;
	rollAngle = 0.0f;
	maxRollAngle = 30.0f;
	desiredRollAngle = 0.0f;

	collisionRadius2 = 0.25f;
	collisionIdentifier = PLAYER_GROUP;
	collisionGroup = ENEMY_GROUP | ENEMY_BULLET_GROUP;

	shooting = false;

	health = 3;
}

Player::~Player()
{

}

void Player::setModel(std::vector<sf::Vector3f> model)
{
	Player::model = model;
}

std::vector<sf::Vector3f> Player::getModel()
{
	return Player::model;
}

void Player::setDirection(sf::Vector2f direction)
{
	this->direction = direction;

	desiredRollAngle = maxRollAngle * direction.x;
}

void Player::draw()
{
	glColor3f(0.1f, 0.5f, 0.1f);
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glRotatef(rollAngle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < Player::model.size(); ++i)
	{
		sf::Vector3f currentVertex = Player::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor* Player::act(float frameTime)
{
	position += direction * speed * frameTime;

	if (!playField->checkIfInside(position))
		position = playField->clampVector(position);

	rollAngle += getRollSpeed() * frameTime;
	if (rollAngle < 0.0f && desiredRollAngle < 0.0f && rollAngle < desiredRollAngle
		|| rollAngle > 0.0f && desiredRollAngle > 0.0f && rollAngle > desiredRollAngle)
		rollAngle = desiredRollAngle;

	timer += frameTime;
	if (shooting && timer > 0.33f)
	{
		timer = 0.0f;
		return new PlayerBullet(this->position, sf::Vector2f(0.0f, 1.0f));
	}

	return 0;
}

Effect* Player::onCollision(Actor* actor)
{
	--health;
	if (health > 0)
		return nullptr;
	else
	{
		setActive(false);
		setAlive(false);
		return new Explosion(this->position, EXPLOSION_SIZE::LARGE);
	}
}

bool Player::getShooting()
{
	return shooting;
}

void Player::setShooting(bool shooting)
{
	this->shooting = shooting;
}

float Player::getRollSpeed()
{
	float rollSpeed = 6.0f*(desiredRollAngle - rollAngle);
	if (abs(rollSpeed) < 10.0f)
	{
		if (rollSpeed < 0)
			rollSpeed = -10.0f;
		else
			rollSpeed = 10.0f;
	}

	return rollSpeed;
}
