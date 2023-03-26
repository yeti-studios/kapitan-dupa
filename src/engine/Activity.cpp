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
		entity->spawnTime = al::GetTime();
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

void Activity::preRender()
{

}

void Activity::postRender()
{

}

void Activity::commonTick()
{
	std::vector<std::string> deadKeys;
	for(auto& [key, entity]: entities) {
		if(entity->isDead()) {
			deadKeys.push_back(key);
		}
	}
	for(auto& key: deadKeys) {
		entities.erase(key);
	}
}

std::string Activity::generateEntityKey() const
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());

	std::string ret;
	do {
		ret = al::Format("%08X%08X", dist(mt), dist(mt));
	} while(entities.contains(ret));
	return ret;
}
