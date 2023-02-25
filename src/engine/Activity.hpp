//
// Created by volt on 2023-02-18.
//

#ifndef KPTDUPA_ACTIVITY_HPP
#define KPTDUPA_ACTIVITY_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <type_traits>

#include "Entity.hpp"

class Engine;

class Activity {
public:

	Entity * getEntityByName(const std::string &name);

	template<typename EntityT, typename... Args> requires std::is_base_of_v<Entity, EntityT>
	bool spawn(const std::string& name, Args... args)
	{
		if(not entities.contains(name)) {
			entities.insert({name, std::unique_ptr<Entity>(new EntityT(args...))});
			return true;
		}
		return false;
	}

	void dispatchEvent(const ALLEGRO_EVENT& ev);
	void renderAllEntities();

	virtual void init() = 0;
	virtual void tick() = 0;

	virtual void start() = 0;
	virtual void stop() = 0;

private:
	friend class Engine;
	void setEngine(Engine* pEngine);
	Engine* engine;
	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
};


#endif //KPTDUPA_ACTIVITY_HPP
