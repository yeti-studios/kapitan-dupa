//
// Created by volt on 2023-02-26.
//

#ifndef KPTDUPA_HIGHSCORESACTIVITY_HPP
#define KPTDUPA_HIGHSCORESACTIVITY_HPP

#include "../engine/all.hpp"
#include "../entities/Button.hpp"

class HighscoresActivity: public Activity {
public:
	HighscoresActivity();

	void init() override;
	void tick() override;
	void start() override;
	void stop() override;

	void postRender() override;

private:
	al::AudioStream music;
	std::shared_ptr<Button> btnReturn;
	std::shared_ptr<Text> titleText;
	std::shared_ptr<Image> background;
};


#endif //KPTDUPA_HIGHSCORESACTIVITY_HPP
