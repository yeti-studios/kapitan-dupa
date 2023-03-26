
#include "game/entities/Pedal7.hpp"
#include "engine/Activity.hpp"
#include "engine/Engine.hpp"
#include "game/activities/MenuActivity.hpp"
#include "game/activities/HighscoresActivity.hpp"
#include "game/activities/GameActivity.hpp"
#include "game/activities/IntroLPGActivity.hpp"
#include "game/activities/IntroYetiActivity.hpp"


int main(int, char**) 
{
    al::FullInit();
    std::set_terminate(al::Terminate);
	al::SampleInstance::ReserveSamples(16);

    Engine engine {{}};
	engine.createActivity<MenuActivity>("mainmenu");
	engine.createActivity<GameActivity>("game");
	engine.createActivity<HighscoresActivity>("highscores");
	engine.createActivity<IntroLPGActivity>("introlpg");
	engine.createActivity<IntroYetiActivity>("introyeti");
	engine.switchToActivity("introlpg");

	engine.run();
}
