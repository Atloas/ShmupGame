#include "Behaviours.h"



Behaviours::Behaviours()
{
}


Behaviours::~Behaviours()
{
}

void Behaviours::moveForwards(Enemy & subject, float frameTime)
{
	subject.setPosition(subject.getPosition() + subject.getDirection()*subject.getMoveSpeed()*frameTime);
}
