//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_ENGINE_HPP
#define KPTDUPA_ENGINE_HPP

#include <memory>
#include <unordered_map>

#include <axxegro/axxegro.hpp>
#include <axxegro/display/DisplayModes.hpp>

#include "Activity.hpp"
#include "StringMap.hpp"
#include "Exception.hpp"

struct EngineOptions {
	al::Vec2i displaySize = {800, 600};
	std::optional<int> maxFramerate = 120;



	static EngineOptions parse(std::string_view json);
	[[nodiscard]] std::string toJSON() const;
};

class Engine {
public:
	explicit Engine(const EngineOptions& options);

	template<typename T> requires std::is_base_of_v<Activity, T>
	void createActivity(const std::string_view name)
	{
		if(activities.contains(name)) {
			throw EngineException("Cannot create activity with duplicate name {}", name);
		}
		auto act =  std::unique_ptr<Activity>(new T());
		act->setEngine(this);
		act->init();
		activities[std::string(name)] = std::move(act);
	}

	Activity* getActivityByName(std::string_view name);
	void switchToActivity(std::string_view name);

	void run();

	const EngineOptions& getOptions();
private:
	Activity* currentActivity;
	StringMap<std::unique_ptr<Activity>> activities;

	EngineOptions options;

	bool exitFlag = false;

	al::Display disp;
	al::Timer framerateLimitTimer;
	al::EventQueue inputEventQueue;
	al::EventQueue timerEventQueue;
};


#endif //KPTDUPA_ENGINE_HPP
