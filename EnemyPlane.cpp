#include "EnemyPlane.h"

#include <SFML\OpenGL.hpp>

#include "EnemyBullet.h"
#include "Explosion.h"

std::vector<sf::Vector3f> EnemyPlane::model;

EnemyPlane::EnemyPlane(sf::Vector2f position, sf::Vector2f direction) : Actor(position, direction)
{
	id = ENEMY_PLANE_ID;

	height = 50.0f;

	speed = 7.5f;

	collisionRadius2 = 1.0f;
	collisionIdentifier = ENEMY_GROUP;
	collisionGroup = PLAYER_GROUP | PLAYER_BULLET_GROUP;

	health = 2;
}

EnemyPlane::~EnemyPlane()
{

}

void EnemyPlane::setModel(std::vector<sf::Vector3f> model)
{
	EnemyPlane::model = model;
}

std::vector<sf::Vector3f> EnemyPlane::getModel()
{
	return EnemyPlane::model;
}

void EnemyPlane::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glRotatef(yawAngle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (unsigned int i = 0; i < EnemyPlane::model.size(); ++i)
	{
		sf::Vector3f currentVertex = EnemyPlane::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor* EnemyPlane::act(float frameTime)
{
	position += direction * speed * frameTime;

	timer += frameTime;
	if (active && timer > 1.5f)
	{
		timer = 0.0f;
		return new EnemyBullet(this->position, this->direction);
	}

	return nullptr;
}

Effect* EnemyPlane::onCollision(Actor* actor)
{
	if (actor->getId() == PLAYER_ID)
		health = 0;

	--health;
	if (health > 0)
		return nullptr;
	else
	{
		setActive(false);
		setAlive(false);
		return new Explosion(this->position, EXPLOSION_SIZE::MEDIUM);
	}
}
