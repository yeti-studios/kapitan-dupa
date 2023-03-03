//
// Created by volt on 2023-02-18.
//

#include "Activity.hpp"

Entity * Activity::getEntityByName(const std::string &name)
{
	if(entities.contains(name)) {
		return entities.at(name).get();
	}
	return nullptr;
}

void Activity::dispatchEvent(const ALLEGRO_EVENT &ev)
{
	if(handleEvent(ev)) {
		return;
	}
	for(auto& [entityId, entity]: entities) {
		entity->handle(ev);
	}
}

void Activity::renderAllEntities()
{
	std::vector<Entity*> sortedEntities;
	sortedEntities.reserve(entities.size());
	std::transform(entities.begin(), entities.end(), std::back_inserter(sortedEntities), [](const auto& v){return v.second.get();});
	std::sort(sortedEntities.begin(), sortedEntities.end(), [](Entity* a, Entity* b){return a->zIndex < b->zIndex;});

	for(Entity* entity: sortedEntities) {
		entity->render();
	}
}

void Activity::setEngine(Engine *pEngine)
{
	this->engine = pEngine;
}

bool Activity::addEntity(const std::string_view name, const std::shared_ptr<Entity>& entity)
{
	if(not entities.contains(name)) {
		entities.insert({std::string(name), entity});
		entity->setActivity(this);
		return true;
	}
	return false;
}

void Activity::updateAllEntities()
{
	for(auto& [entityId, entity]: entities) {
		entity->update();
	}
}

Engine *Activity::getEngine() const
{
	return engine;
}

bool Activity::handleEvent(const ALLEGRO_EVENT &ev)
{
	return false;
}

void Activity::triggerStart()
{
	startTime = al::GetTime();
	start();
}

double Activity::timeSinceStart() const
{
	return al::GetTime() - startTime;
}
