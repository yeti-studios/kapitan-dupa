//
// Created by volt on 2023-02-20.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_ENGINE_HPP
#define KPTDUPA_ENGINE_HPP

#include "StringMap.hpp"
#include "Exception.hpp"

#include "Activity.hpp"

struct EngineOptions {
	al::Vec2i displaySize = {800, 600};
	std::optional<int> maxFramerate = 165;



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
		auto act = std::shared_ptr<Activity>(new T());
		act->setEngine(this);
		act->init();
		activities[std::string(name)] = std::move(act);
	}

	Activity* getActivityByName(std::string_view name);
	void switchToActivity(std::string_view name);

	void run();
	al::Font& font();

	const EngineOptions& getOptions();
	void setExitFlag();
private:
	al::Display disp;
	Activity* currentActivity;
	StringMap<std::shared_ptr<Activity>> activities;

	EngineOptions options;
	al::Font defaultFont;

	bool exitFlag = false;

	al::Timer framerateLimitTimer;
	al::EventQueue inputEventQueue;
	al::EventQueue timerEventQueue;
};


#endif //KPTDUPA_ENGINE_HPP
