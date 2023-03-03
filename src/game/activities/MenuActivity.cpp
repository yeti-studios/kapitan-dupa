//
// Created by volt on 2023-02-20.
//


#include "MenuActivity.hpp"
#include "../entities/Pedal7.hpp"
#include "../engine/Engine.hpp"


MenuActivity::MenuActivity()
		: menuMusic("res/music/planetacountry.ogg")
{

}


void MenuActivity::init()
{
	pedal7 = spawn<Pedal7>("pedal7");
	starBg = spawn<StarBackground>("starbg");
	titleText = spawn<Image>("titletext", "res/img/title.png");
	menubg = spawn<Image>("menubg", "res/img/menubg.jpg");

	btnNewGame = spawn<Button>("btnNewGame", "Nowa gra", al::Rect<>::XYWH(100, 350, 180, 36));
	btnHighscores = spawn<Button>("btnHighscores", "Twardziele", al::Rect<>::XYWH(100, 390, 180, 36));
	btnExit = spawn<Button>("btnExit", "Wyjdź", al::Rect<>::XYWH(100, 430, 180, 36));

	btnNewGame->onclick = [&](){
		getEngine()->switchToActivity("game");
	};

	btnHighscores->onclick = [&](){
		getEngine()->switchToActivity("highscores");
	};

//	btnOptions->onclick = [&](){
//
//	};

	btnExit->onclick = [&](){
		getEngine()->setExitFlag();
	};

	titleText->setRect(al::Rect<>::XYWH(29, 39, 481, 208));
	pedal7->setRect(al::Rect<float>::XYWH(390, 120, 360, 145));
	starBg->zIndex = -90;
	menubg->zIndex = -91;
	//menubg->tint = al::RGB(40, 50, 60);
	menubg->tint = al::RGBA(0, 0, 0, 0);
}

void MenuActivity::tick()
{

}

void MenuActivity::stop()
{
	menuMusic.detach();
	menuMusic.setPlaying(false);
}

void MenuActivity::start()
{
	menuMusic.rewind();
	menuMusic.setPlaying(true);
	menuMusic.setPlayMode(ALLEGRO_PLAYMODE_LOOP);
	al::DefaultMixer.attachAudioStream(menuMusic);
}

bool MenuActivity::handleEvent(const ALLEGRO_EVENT &ev)
{
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			getEngine()->setExitFlag();
			return true;
		}
	}
	return false;
}
