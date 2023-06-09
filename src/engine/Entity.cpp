//
// Created by volt on 2023-02-26.
//

#include "Entity.hpp"
#include "Activity.hpp"
#include "Engine.hpp"


Activity *Entity::getActivity() const
{
	return activity;
}

Engine *Entity::getEngine() const
{
	return activity->getEngine();
}

void Entity::setActivity(Activity *activity1)
{
	activity = activity1;
}

void Entity::kill()
{
	dead = true;
}

bool Entity::isDead() const
{
	return dead;
}

double Entity::timeSinceSpawn() const
{
	return al::GetTime() - spawnTime;
}
