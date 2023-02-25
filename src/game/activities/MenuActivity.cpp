//
// Created by volt on 2023-02-20.
//

#include <axxegro/audio/Audio.hpp>

#include "MenuActivity.hpp"
#include "../entities/Pedal7.hpp"

void MenuActivity::init()
{
	spawn<Pedal7>("pedal7");


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

MenuActivity::MenuActivity()
	: menuMusic("res/music/planetacountry.ogg")
{

}
