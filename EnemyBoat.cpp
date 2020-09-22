#include "EnemyBoat.h"

#include <SFML/OpenGL.hpp>

#include "Explosion.h"
#include "Utils.h"

std::vector<sf::Vector3f> EnemyBoat::model;

EnemyBoat::EnemyBoat(sf::Vector2f position, sf::Vector2f direction, Player* player) : Actor(position, direction)
{
	id = ENEMY_BOAT_ID;

	turret = new EnemyTurret(this->position, direction, player, sf::Vector2f(0.0f, -0.25f));
	turret->setHostYawAngle(yawAngle);

	height = 1.5f;

	speed = 3.5f;

	collisionRadius2 = 1.0f;
	collisionIdentifier = ENEMY_GROUP;
	collisionGroup = PLAYER_GROUP | PLAYER_BULLET_GROUP;

	health = 5;
}


EnemyBoat::~EnemyBoat()
{
	delete turret;
}

void EnemyBoat::setModel(std::vector<sf::Vector3f> model)
{
	EnemyBoat::model = model;
}

std::vector<sf::Vector3f> EnemyBoat::getModel()
{
	return EnemyBoat::model;
}

void EnemyBoat::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glRotatef(yawAngle, 0.0f, 0.0f, 1.0f);
	turret->draw();
	glBegin(GL_TRIANGLES);
	glColor3f(0.33f, 0.33f, 0.33f);
	for (unsigned int i = 0; i < EnemyBoat::model.size(); ++i)
	{
		sf::Vector3f currentVertex = EnemyBoat::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor * EnemyBoat::act(float frameTime)
{
	position += direction * speed * frameTime;

	turret->setPosition(position);

	return turret->act(frameTime);
}

Effect * EnemyBoat::onCollision(Actor * actor)
{
	if (actor->getId() == PLAYER_ID)
		health = 0;

	health--;
	if (health > 0)
		return nullptr;
	else
	{
		setActive(false);
		setAlive(false);
		return new Explosion(this->position, EXPLOSION_SIZE::LARGE);
	}
}

void EnemyBoat::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
	yawAngle = Utils::convertToDegrees(Utils::getAngleFromUpwards(direction));
	turret->setHostYawAngle(yawAngle);
}

void EnemyBoat::setActive(bool active)
{
	this->active = active;
	turret->setActive(active);
}

void EnemyBoat::setAlive(bool alive)
{
	this->alive = alive;
	turret->setAlive(alive);
}

void EnemyBoat::setCollideable(bool collideable)
{
	//Turret can't be hit in the current Boat implementation anyway, this'd only make sense if the turrets were able to be destroyed separately, maybe in the future?
	this->collideable = collideable;
	turret->setCollideable(collideable);
}

EnemyTurret * EnemyBoat::getTurret()
{
	return turret;
}

void EnemyBoat::setTurret(EnemyTurret * turret)
{
	this->turret = turret;
}
