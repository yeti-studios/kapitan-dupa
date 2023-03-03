//
// Created by volt on 2023-02-20.
//

#include <kptdup_pch.hpp>

#ifndef KPTDUPA_MENUACTIVITY_HPP
#define KPTDUPA_MENUACTIVITY_HPP

#include "../../engine/Activity.hpp"
#include "../entities/Pedal7.hpp"
#include "../entities/StarBackground.hpp"
#include "../entities/Button.hpp"

class MenuActivity: public Activity {
public:
	MenuActivity();

	void init() override;
	void tick() override;

	void start() override;
	void stop() override;

	bool handleEvent(const ALLEGRO_EVENT &ev) override;

private:
	al::AudioStream menuMusic;
	std::shared_ptr<Pedal7> pedal7;
	std::shared_ptr<Image> titleText;
	std::shared_ptr<StarBackground> starBg;
	std::shared_ptr<Image> menubg;

	std::shared_ptr<Button> btnNewGame, btnOptions, btnHighscores, btnExit;
};


#endif //KPTDUPA_MENUACTIVITY_HPP
