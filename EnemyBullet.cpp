#include "EnemyBullet.h"

#include <SFML\OpenGL.hpp>

#include "Explosion.h"

std::vector<sf::Vector3f> EnemyBullet::model;

EnemyBullet::EnemyBullet(sf::Vector2f position, sf::Vector2f direction) : Actor(position, direction)
{
	id = ENEMY_BULLET_ID;

	height = 98.0f;

	speed = 12.5f;

	collisionRadius2 = 0.125f;
	collisionIdentifier = ENEMY_BULLET_GROUP;
	collisionGroup = PLAYER_GROUP;
}


EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::setModel(std::vector<sf::Vector3f> model)
{
	EnemyBullet::model = model;
}

std::vector<sf::Vector3f> EnemyBullet::getModel()
{
	return EnemyBullet::model;
}

void EnemyBullet::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glRotatef(yawAngle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.3f, 0.3f);
	for (unsigned int i = 0; i < EnemyBullet::model.size(); i++)
	{
		sf::Vector3f currentVertex = EnemyBullet::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor* EnemyBullet::act(float frameTime)
{
	position += direction * speed * frameTime;

	return nullptr;
}

Effect* EnemyBullet::onCollision(Actor* actor)
{
	setActive(false);
	setAlive(false);
	return new Explosion(this->position, EXPLOSION_SIZE::SMALL);
}
