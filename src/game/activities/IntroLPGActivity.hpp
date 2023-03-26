//
// Created by volt on 2023-03-03.
//

#ifndef KPTDUPA_INTROLPGACTIVITY_HPP
#define KPTDUPA_INTROLPGACTIVITY_HPP

#include "../engine/all.hpp"

class IntroLPGActivity: public Activity {
public:
	IntroLPGActivity();

	void init() override;
	void tick() override;
	void start() override;
	void stop() override;
	bool handleEvent(const ALLEGRO_EVENT &ev) override;

	void postRender() override;

	void skip();

	std::shared_ptr<Image> txt, bglpg, poldek, flare;
	al::Sample audioSmp;
	al::SampleInstance audioSmpInst;
};


#endif //KPTDUPA_INTROLPGACTIVITY_HPP
