//
// Created by volt on 2023-03-03.
//

#include "IntroLPGActivity.hpp"

IntroLPGActivity::IntroLPGActivity()
		: audioSmp("res/music/intro_lpg.ogg"),
		  audioSmpInst(audioSmp)
{

}

void IntroLPGActivity::init()
{
	txt = spawn<Image>("txt", "res/img/introlpg.png");
	bglpg = spawn<Image>("bglpg", "res/img/lpg.jpg");
	poldek = spawn<Image>("poldek", "res/img/poldek.jpg");
	flare = spawn<Image>("flare", "res/img/blueflare.png");

	flare->setRect(flare->rect() + al::Vec2f(215, 250) - (flare->rect().size()/2.0f));
	flare->zIndex = 37;

	txt->zIndex = 10;
	bglpg->zIndex = -1;
	bglpg->tint = al::Gray(0.2);
	poldek->setRect(al::CurrentDisplay.rect());
	poldek->zIndex = 0;
}

void IntroLPGActivity::tick()
{
	float opacity = (float)std::min(1.0, timeSinceStart());
	txt->tint = al::RGBA_f(opacity, opacity, opacity, opacity);



	if(timeSinceStart() > 0.01 && !audioSmpInst.getPlaying()) {
		skip();
	}

	float scale = 1.0 + exp(-timeSinceStart() * 3.0);
	al::Vec2f center = al::CurrentDisplay.rect().center();
	al::Vec2f dA = al::CurrentDisplay.rect().a - center;
	al::Vec2f dB = al::CurrentDisplay.rect().b - center;
	bglpg->setRect(al::Rect<float>(center + (dA*scale), center + (dB*scale)));

	if(timeSinceStart() > 3.7) {
		poldek->tint = al::Gray(0.2);
	}

	auto gauss = [](double x){
		return std::exp(-x*x);
	};

	float flareIntensity = 1.0 * gauss(4.0 * (timeSinceStart() - 0.5));
	flare->tint = al::RGBA_f(flareIntensity, flareIntensity, flareIntensity, flareIntensity);
}

void IntroLPGActivity::start()
{

	al::DefaultMixer.attachSampleInstance(audioSmpInst);
	audioSmpInst.setPosition(0);
	audioSmpInst.setPlaying(true);

	poldek->tint = al::RGBA(0,0,0,0);

}

void IntroLPGActivity::stop()
{
	audioSmpInst.detach();
	audioSmpInst.setPlaying(false);


	for(auto& img: {txt, bglpg, flare, poldek}) {
		img->unload();
	}
}

bool IntroLPGActivity::handleEvent(const ALLEGRO_EVENT &ev)
{
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		for(auto skipKey: {ALLEGRO_KEY_ESCAPE, ALLEGRO_KEY_ENTER, ALLEGRO_KEY_SPACE}) {
			if(ev.keyboard.keycode == skipKey) {
				skip();
				return true;
			}
		}
	}
	return Activity::handleEvent(ev);
}

void IntroLPGActivity::skip()
{
	getEngine()->switchToActivity("introyeti");
}

void IntroLPGActivity::postRender()
{
	//TODO factor this out to IntroSequenceActivity

	double start = 0.0f;
	double end = audioSmpInst.getLengthSecs();
	double pos = (double)audioSmpInst.getPosition() / audioSmpInst.getFrequency();

	double dist = std::min(std::abs(start-pos), std::abs(end-pos));
	double opacity = std::min(dist * 1.7, 1.0);

	al::Color tint = al::RGBA_f(0, 0, 0, 1.0 - opacity);
	al::DrawFilledRectangle(al::CurrentDisplay.rect(), tint);
}

