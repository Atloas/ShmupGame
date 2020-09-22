#include "PlayerBullet.h"

#include <SFML\OpenGL.hpp>

#include "Explosion.h"
#include "PlayerBulletExplosion.h"

std::vector<sf::Vector3f> PlayerBullet::model;

PlayerBullet::PlayerBullet(sf::Vector2f position, sf::Vector2f direction) : Actor(position, direction)
{
	id = PLAYER_BULLET_ID;

	height = 90.0f;

	speed = 25.0f;

	collisionRadius2 = 0.125f;
	collisionIdentifier = PLAYER_BULLET_GROUP;
	collisionGroup = ENEMY_GROUP;
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::setModel(std::vector<sf::Vector3f> model)
{
	PlayerBullet::model = model;
}

std::vector<sf::Vector3f> PlayerBullet::getModel()
{
	return PlayerBullet::model;
}

void PlayerBullet::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.9f, 0.2f);
	for (unsigned int i = 0; i < PlayerBullet::model.size(); i++)
	{
		sf::Vector3f currentVertex = PlayerBullet::model.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

Actor* PlayerBullet::act(float frameTime)
{
	position += direction * speed * frameTime;

	return nullptr;
}

Effect* PlayerBullet::onCollision(Actor* actor)
{
	setActive(false);
	setAlive(false);
	//return new PlayerBulletExplosion(this->position);
	return new Explosion(position, EXPLOSION_SIZE::SMALL);
}
