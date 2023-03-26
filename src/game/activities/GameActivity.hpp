//
// Created by volt on 2023-02-20.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_GAMEACTIVITY_HPP
#define KPTDUPA_GAMEACTIVITY_HPP

#include "../../engine/all.hpp"
#include "../entities/FaggotPair.hpp"

class GameActivity: public Activity {
public:
	enum class GameState {
		Initial,
		Countdown,
		Gameplay,
		Summary,
		LoginPrompt,
		PostGame
	};

	GameActivity();

	void init() override;
	void tick() override;
	void start() override;
	void stop() override;
	bool handleEvent(const ALLEGRO_EVENT &ev) override;

	void preRender() override;
	void postRender() override;

	void playSummarySound();
	void postSummary();
	void endGame();
	std::string loginStr() const;
	std::string loginStrClean() const;

	double gameLength = 15.00;

	GameState gameState = GameState::Initial;
	double lastStateChange;
	double timeLeft = gameLength;
	double timeSinceStateChange() const;
	void setState(GameState gameState1);

	int score = 0;
	int lastSpeech = 0;

	al::Sample sndIn, sndOut, sndCountdown, sndStart, sndGameOver, sndLowScore, sndHighScore, sndLoginPrompt, sndJingle, sndUnsat;
	std::vector<al::Sample> gameplaySpeechSamples;
	al::SampleInstance speechInst;
	std::u32string loginInput;

	std::shared_ptr<FaggotPair> faggots;


private:

};


#endif //KPTDUPA_GAMEACTIVITY_HPP
