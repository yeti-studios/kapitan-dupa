//
// Created by volt on 2023-02-18.
//

#include <vector>
#include <algorithm>
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
