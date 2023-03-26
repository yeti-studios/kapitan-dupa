//
// Created by volt on 2023-02-20.
//

#include "Engine.hpp"

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
	  defaultFont("res/neuropol.ttf", 24),
	  disp(options.displaySize.x, options.displaySize.y),
	  framerateLimitTimer(1.0 / options.maxFramerate.value_or(120.0))
{
	al::Bitmap::SetNewBitmapFlags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

	inputEventQueue.registerSource(al::GetKeyboardEventSource());
	inputEventQueue.registerSource(al::GetMouseEventSource());
	inputEventQueue.registerSource(disp.eventSource());

	timerEventQueue.registerSource(framerateLimitTimer.getEventSource());
	if(options.maxFramerate.has_value()) {
		framerateLimitTimer.start();
	}

	static al::Bitmap mouseCursorBitmap("res/img/mouse.png");
	static al::MouseCursor mouseCursor(mouseCursorBitmap, {0,0});

	disp.setCursor(mouseCursor);
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
		currentActivity->triggerStart();
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
	//auto keybDiscrId = dispatcher.addDiscretizer({ALLEGRO_EVENT_KEY_DOWN, [](const ALLEGRO_EVENT& ev){return ev.keyboard.keycode;}});

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

		if(auto* act1 = currentActivity) {
			currentActivity->commonTick();
			currentActivity->tick();
			currentActivity->updateAllEntities();
			currentActivity->preRender();
			currentActivity->renderAllEntities();
			currentActivity->postRender();
		}

		al::CurrentDisplay.flip();
	}

	exitFlag = false;
}

const EngineOptions &Engine::getOptions()
{
	return options;
}

al::Font &Engine::font()
{
	return defaultFont;
}

void Engine::setExitFlag()
{
	exitFlag = true;
}
