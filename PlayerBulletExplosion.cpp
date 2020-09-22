#include "PlayerBulletExplosion.h"

#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>

#include "IDs.h"

PlayerBulletExplosion::PlayerBulletExplosion(sf::Vector2f position) : Effect(position)
{
	id = PLAYER_BULLET_EXPLOSION_ID;
}


PlayerBulletExplosion::~PlayerBulletExplosion()
{

}

void PlayerBulletExplosion::draw()
{
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glColor3f(1.0f, 0.7f, 0.0f);
	gluSphere(quadric, 0.5f, 8, 8);
	glPopMatrix();
	gluDeleteQuadric(quadric);
}

void PlayerBulletExplosion::tick(float frameTime)
{
	timer += frameTime;
	if (timer > 0.25f)
		setAlive(false);
}
