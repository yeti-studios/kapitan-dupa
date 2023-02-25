
#include <axxegro/axxegro.hpp>


#include "game/entities/Pedal7.hpp"
#include "engine/Activity.hpp"
#include "engine/Engine.hpp"
#include "game/activities/MenuActivity.hpp"

int main(int, char**) 
{
    al::FullInit();
    std::set_terminate(al::Terminate);
	al::SampleInstance::ReserveSamples(16);

    Engine engine {{}};
	engine.createActivity<MenuActivity>("mainmenu");
	engine.switchToActivity("mainmenu");


	engine.run();
}
