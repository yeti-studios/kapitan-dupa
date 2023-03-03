//
// Created by volt on 2023-02-26.
//

#include "HighscoresActivity.hpp"

HighscoresActivity::HighscoresActivity()
	: music("res/music/mocnyamper.ogg")
{

}

void HighscoresActivity::init()
{
	btnReturn = spawn<Button>("btnReturn", "Powrót", al::Rect<>::XYWH(100, 500, 200, 50));
	btnReturn->onclick = [&](){
		getEngine()->switchToActivity("mainmenu");
	};

	titleText = spawn<Text>("titleText", "Najluźniejsze dupska", al::Vec2f {400.0f, 20.0f}, al::PureGreen);
	background = spawn<Image>("bg", "res/img/hsbg.png");
	background->zIndex = -91;
	background->tint = al::RGB(20, 20, 20);
}

void HighscoresActivity::tick()
{

}

void HighscoresActivity::start()
{
	music.rewind();
	al::DefaultMixer.attachAudioStream(music);
	music.setPlaying(true);
}

void HighscoresActivity::stop()
{
	music.detach();
	music.setPlaying(false);
}
