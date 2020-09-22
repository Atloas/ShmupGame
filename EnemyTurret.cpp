#include "EnemyTurret.h"

#include <SFML/OpenGL.hpp>

#include "Explosion.h"
#include "EnemyBullet.h"
#include "Utils.h"

std::vector<sf::Vector3f> EnemyTurret::model;

EnemyTurret::EnemyTurret(sf::Vector2f position, sf::Vector2f direction, Player* player, sf::Vector2f hostOriginOffset) : Actor(position, direction)
{
	id = ENEMY_TURRET_ID;

	this->player = player;
	this->hostOriginOffset = hostOriginOffset;
	height = 1.0f;						//Height for turrets is an offset from the host

	hostYawAngle = 0.0f;

	speed = 0.0f;

	collisionRadius2 = 1.0f;
	collisionIdentifier = ENEMY_GROUP;
	collisionGroup = PLAYER_GROUP | PLAYER_BULLET_GROUP;

	health = 3;
}


EnemyTurret::~EnemyTurret()
{

}

void EnemyTurret::setModel(std::vector<sf::Vector3f> model)
{
	EnemyTurret::model = model;
}

std::vector<sf::Vector3f> EnemyTurret::getModel()
{
	return EnemyTurret::model;
}

void EnemyTurret::draw()
{
	glPushMatrix();
	glTranslatef(hostOriginOffset.x, hostOriginOffset.y, height);
	glRotatef(-hostYawAngle + yawAngle , 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.425f, 0.425f, 0.425f);
	for (unsigned int i = 0; i < EnemyTurret::model.size(); ++i)
	{
		sf::Vector3f currentVertex = EnemyTurret::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor * EnemyTurret::act(float frameTime)
{
	sf::Vector2f vectorToPlayer = player->getPosition() - position;
	sf::Vector2f newDirection(vectorToPlayer.x, vectorToPlayer.y);
	setDirection(Utils::normalizeVector(newDirection));

	timer += frameTime;
	if (timer >= 2.0f)
	{
		timer = 0.0f;
		return new EnemyBullet(position, direction);
	}

	return nullptr;
}

Effect * EnemyTurret::onCollision(Actor * actor)
{
	health--;
	if (health > 0)
		return nullptr;
	else
	{
		setActive(false);
		setAlive(false);
		return new Explosion(this->position, EXPLOSION_SIZE::MEDIUM);
	}
}

float EnemyTurret::getHostYawAngle()
{
	return hostYawAngle;
}

void EnemyTurret::setHostYawAngle(float hostYawAngle)
{
	this->hostYawAngle = hostYawAngle;
}

sf::Vector2f EnemyTurret::getHostOriginOffset()
{
	return hostOriginOffset;
}

void EnemyTurret::setHostOriginOffset(sf::Vector2f hostOriginOffset)
{
	this->hostOriginOffset = hostOriginOffset;
}
