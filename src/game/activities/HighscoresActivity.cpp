//
// Created by volt on 2023-02-26.
//

#include "HighscoresActivity.hpp"
#include "../Highscores.hpp"

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

	titleText = spawn<Text>("titleText", "Najluźniejsze dupska", al::Vec2f {400.0f, 20.0f}, al::LightCyan);
	background = spawn<Image>("txt", "res/img/hsbg.png");
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

void HighscoresActivity::postRender()
{
	auto highscores = Highscores::getInstance().getHighscores();
	auto& font = getEngine()->font();

	for(int i=-1; i<10; i++) {
		int h = font.getLineHeight() + 5;
		int y = 110 + i*(h + 5);

		al::Rect<> col1r(150, y, 395, y+h);
		al::Rect<> col2r(405, y, 650, y+h);

		al::Color colbg = al::RGBA_f(0, 0.05, 0, 0.4);
		al::DrawFilledRectangle(col1r, colbg);
		al::DrawFilledRectangle(col2r, colbg);

		al::Vec2f txtoff(0, -0.5f * font.getAscent());

		std::string c1 = "Login";
		std::string c2 = "Wynik";

		if(i >= 0) {
			if(i < highscores.size()) {
				c1 = highscores[i].login;
				c2 = std::to_string(highscores[i].score);
			} else {
				c1 = "-";
				c2 = "-";
			}
		}

		al::Color txtcol = (i>=0) ? al::PureGreen : al::PureYellow;
		font.draw(c1, txtcol, col1r.center() + txtoff, ALLEGRO_ALIGN_CENTER);
		font.draw(c2, txtcol, col2r.center() + txtoff, ALLEGRO_ALIGN_CENTER);
	}
}
