//
// Created by volt on 2023-02-20.
//

#include "Engine.hpp"

#include <nlohmann/json.hpp>

EngineOptions EngineOptions::parse(const std::string_view json)
{
	throw NotImplementedException("");
}

std::string EngineOptions::toJSON() const
{
	throw NotImplementedException("");
}

Engine::Engine(const EngineOptions &options)
	: options(options),
	  currentActivity(nullptr),
	  disp(options.displaySize.x, options.displaySize.y),
	  framerateLimitTimer(1.0 / options.maxFramerate.value_or(120.0))
{
	inputEventQueue.registerSource(al::GetKeyboardEventSource());
	inputEventQueue.registerSource(al::GetMouseEventSource());
	inputEventQueue.registerSource(disp.eventSource());

	timerEventQueue.registerSource(framerateLimitTimer.getEventSource());
	if(options.maxFramerate.has_value()) {
		framerateLimitTimer.start();
	}

	disp.setTitle("Kapitan Dupa");
}

Activity *Engine::getActivityByName(const std::string_view name)
{
	if(activities.contains(name))
		return activities.find(name)->second.get();
	return nullptr;
}

void Engine::switchToActivity(const std::string_view name)
{
	if(auto* newActivity = getActivityByName(name)) {
		if(currentActivity) {
			currentActivity->stop();
		}
		currentActivity = newActivity;
		currentActivity->start();
	}
}

void Engine::run()
{
	al::EventDispatcher dispatcher;
	dispatcher.setDefaultHandler([this](const ALLEGRO_EVENT& ev){
		if(currentActivity) {
			currentActivity->dispatchEvent(ev);
		}
	});
	auto exitHandler = [&](const ALLEGRO_EVENT& ev){exitFlag = true;};
	auto keybDiscrId = dispatcher.addDiscretizer({ALLEGRO_EVENT_KEY_DOWN, [](const ALLEGRO_EVENT& ev){return ev.keyboard.keycode;}});

	dispatcher.setEventValueHandler(keybDiscrId, ALLEGRO_KEY_ESCAPE, exitHandler);
	dispatcher.setEventTypeHandler(ALLEGRO_EVENT_DISPLAY_CLOSE, exitHandler);


	while(!exitFlag) {
		if(options.maxFramerate.has_value()) {
			timerEventQueue.wait();
			timerEventQueue.flush();
		}

		al::TargetBitmap.clear();

		while(!inputEventQueue.empty()) {
			dispatcher.dispatch(inputEventQueue.pop());
		}

		if(currentActivity) {
			currentActivity->tick();
			currentActivity->renderAllEntities();
		}

		al::CurrentDisplay.flip();
	}

	exitFlag = false;
}

const EngineOptions &Engine::getOptions()
{
	return options;
}
