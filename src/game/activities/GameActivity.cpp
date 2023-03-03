//
// Created by volt on 2023-02-20.
//

#include "GameActivity.hpp"

void GameActivity::init()
{

}

void GameActivity::tick()
{

}

void GameActivity::start()
{

}

void GameActivity::stop()
{

}

bool GameActivity::handleEvent(const ALLEGRO_EVENT &ev)
{
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			getEngine()->switchToActivity("mainmenu");
			return true;
		}
	}
	return false;
}
