//
// Created by volt on 2023-03-03.
//

#include "IntroYetiActivity.hpp"

static constexpr double ShakeAnimTimerFreq = 35.0f;

IntroYetiActivity::IntroYetiActivity()
	: audioSmp("res/music/yetistudios.ogg"),
	  audioSmpInst(audioSmp),
	  shakeAnimTimer(al::FreqToPeriod(ShakeAnimTimerFreq))
{

}


void IntroYetiActivity::init()
{
	electrobg = spawn<ScrollingImage>("electrobg", "res/img/electrobg.png");
	electrobg->vertical = true;
	electrobg->tint = al::Gray(0.2);
	electrobg->zIndex = -99;

	titleText = spawn<Image>("titletext", "res/img/introyeti.png");

	yeti = spawn<Image>("yeti", "res/img/yeti.png");
	pissedYeti = spawn<Image>("pissedYeti", "res/img/pissed_yeti.png");
	yeti->render();
	pissedYeti->render();

	yeti->setCenter({530.f, 360.f});
	pissedYeti->setCenter({530.f, 360.f});

	yeti->tint = al::RGBA(0,0,0,0);
	pissedYeti->tint = al::RGBA(0,0,0,0);

	shakeAnimTimerQ.registerSource(shakeAnimTimer.getEventSource());
}



void IntroYetiActivity::tick()
{
	if(timeSinceStart() > 0.01 && !audioSmpInst.getPlaying()) {
		skip();
	}

	titleText->setCenter(al::Vec2f(170.f, 400.0f - (float)std::exp(-timeSinceStart() * 4.0f) * 200.0f));

	if(timeSinceStart() < 2.2) {
		yeti->tint = al::RGBA_f(1,1,1,1);
		pissedYeti->tint = al::RGBA_f(0,0,0,0);
	} else {
		yeti->tint = al::RGBA_f(0,0,0,0);
		pissedYeti->tint = al::RGBA_f(1,1,1,1);
	}

	double shkMagnitude = 10.0f * (M_PI_2 - std::atan(4.0 * (timeSinceStart()-2.7)));
	//std::cout << shkMagnitude << "\n";

	if(not shakeAnimTimerQ.empty()) {
		shakeAnimTimerQ.flush();
		lastSATTick = al::GetTime();

		vrand1 = vrand2;
		vrand2 = RandVec2() * shkMagnitude;
	}

	double satProgress = (al::GetTime() - lastSATTick) * ShakeAnimTimerFreq;
	//std::cout << std::format("satProgress = %f\n", satProgress);
	al::Vec2f shkOffset = vrand1*(1.0-satProgress) + vrand2*satProgress;

	pissedYeti->setCenter(al::Vec2f(530,360) + shkOffset);
}

void IntroYetiActivity::start()
{
	al::DefaultMixer.attachSampleInstance(audioSmpInst);
	audioSmpInst.setPosition(0);
	audioSmpInst.setPlaying(true);

	shakeAnimTimer.start();
}

void IntroYetiActivity::stop()
{
	audioSmpInst.detach();
	audioSmpInst.setPlaying(false);

	shakeAnimTimer.stop();

	electrobg->unload();
	yeti->unload();
	pissedYeti->unload();
}

bool IntroYetiActivity::handleEvent(const ALLEGRO_EVENT &ev)
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

void IntroYetiActivity::skip()
{
	getEngine()->switchToActivity("mainmenu");
}

void IntroYetiActivity::preRender()
{
	electrobg->setProgress(float(timeSinceStart()) * 0.1f);
	Activity::preRender();
}

void IntroYetiActivity::postRender()
{
	double start = 0.0f;
	double end = audioSmpInst.getLengthSecs();
	double pos = (double)audioSmpInst.getPosition() / audioSmpInst.getFrequency();

	double dist = std::min(std::abs(start-pos), std::abs(end-pos));
	double opacity = std::min(dist * 1.7, 1.0);

	al::Color tint = al::RGBA_f(0, 0, 0, 1.0 - opacity);
	al::DrawFilledRectangle(al::CurrentDisplay.rect(), tint);
}
