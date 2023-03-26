//
// Created by volt on 2023-03-03.
//

#ifndef KPTDUPA_INTROYETIACTIVITY_HPP
#define KPTDUPA_INTROYETIACTIVITY_HPP

#include "../engine/all.hpp"
#include "../entities/ScrollingImage.hpp"

class IntroYetiActivity: public Activity {
public:
	IntroYetiActivity();

	void init() override;
	void tick() override;
	void start() override;
	void stop() override;
	bool handleEvent(const ALLEGRO_EVENT &ev) override;
	void skip();

	void preRender() override;

	void postRender() override;

	al::Sample audioSmp;
	al::SampleInstance audioSmpInst;

	std::shared_ptr<ScrollingImage> electrobg;
	std::shared_ptr<Image> titleText, yeti, pissedYeti;

	al::Timer shakeAnimTimer;
	al::EventQueue shakeAnimTimerQ;
	double lastSATTick = -311.0;
	al::Vec2f vrand1, vrand2;
};


#endif //KPTDUPA_INTROYETIACTIVITY_HPP
