//
// Created by volt on 2023-02-18.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_ACTIVITY_HPP
#define KPTDUPA_ACTIVITY_HPP

#include "Entity.hpp"
#include "StringMap.hpp"
#include "Math.hpp"

class Engine;

class Activity {
public:

	Entity * getEntityByName(const std::string &name);

	template<typename EntityT, typename... Args> requires std::is_base_of_v<Entity, EntityT>
	std::shared_ptr<EntityT> spawn(const std::string& name, Args... args)
	{
		std::shared_ptr<Entity> shared{new EntityT(args...)};
		if(addEntity(name, shared)) {
			return std::dynamic_pointer_cast<EntityT>(shared);
		}
		return {};
	}

	template<typename EntityT, typename... Args> requires std::is_base_of_v<Entity, EntityT>
	std::shared_ptr<EntityT> spawnUnique(Args... args)
	{
		return spawn<EntityT>(generateEntityKey(), args...);
	}

	bool addEntity(std::string_view name, const std::shared_ptr<Entity>& entity);

	void dispatchEvent(const ALLEGRO_EVENT& ev);
	void renderAllEntities();
	void updateAllEntities();

	void commonTick();

	virtual void init() = 0;
	virtual void tick() = 0;

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void preRender();
	virtual void postRender();

	virtual bool handleEvent(const ALLEGRO_EVENT& ev);

	Engine* getEngine() const;
	void triggerStart();

	double timeSinceStart() const;

	std::string generateEntityKey() const;
private:
	friend class Engine;
	void setEngine(Engine* pEngine);

	Engine* engine;
	double startTime;
	StringMap<std::shared_ptr<Entity>> entities;
};



#endif //KPTDUPA_ACTIVITY_HPP
