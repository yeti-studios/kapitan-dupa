//
// Created by volt on 2023-02-20.
//

#include "GameActivity.hpp"
#include "../Highscores.hpp"
#include "../entities/PointsInfo.hpp"

GameActivity::GameActivity()
		: sndIn("res/sfx/in.wav"),
		  sndOut("res/sfx/out.wav"),
		  sndCountdown("res/sfx/speech/countdown.wav"),
		  sndStart("res/sfx/start.wav"),
		  sndGameOver("res/sfx/speech/gameover.wav"),
		  sndLowScore("res/sfx/speech/lowscore.wav"),
		  sndHighScore("res/sfx/speech/hiscore.wav"),
		  sndLoginPrompt("res/sfx/speech/lgprompt.wav"),
		  sndJingle("res/sfx/jingle.wav"),
		  sndUnsat("res/sfx/speech/unsatisfied.wav"),
		  speechInst(sndCountdown)
{

}

void GameActivity::init()
{
	faggots = spawn<FaggotPair>("faggots",
		std::make_shared<al::Bitmap>("res/img/dup0.png"),
		std::make_shared<al::Bitmap>("res/img/dup1.png")
	);

	for(int i=1; i<=4; i++) {
		gameplaySpeechSamples.emplace_back(al::Format("res/sfx/speech/ingame%d.wav", i));
	}
}

void GameActivity::tick()
{
	if(gameState == GameState::Countdown) {
		if(timeSinceStateChange() > 1.3) {
			sndStart.play();
			setState(GameState::Gameplay);
		}
	} else if(gameState == GameState::Gameplay) {
		timeLeft = gameLength - timeSinceStateChange();

		if(not speechInst.getPlaying()) {
			int idx = -1;
			do {
				idx = RandInt((int)gameplaySpeechSamples.size());
			} while (idx == lastSpeech);
			lastSpeech = idx;
			speechInst.setSample(gameplaySpeechSamples.at((unsigned)idx));
			speechInst.setPlaying(true);
		}

		if(timeLeft < 0) {
			timeLeft = 0;
			speechInst.setSample(sndGameOver);
			speechInst.setPlaying(true);
			setState(GameState::Summary);
		}
	} else if(gameState == GameState::Summary) {
		static bool summarySoundPlayed = false;
		if(not speechInst.getPlaying()) {
			if(not summarySoundPlayed) {
				playSummarySound();
				summarySoundPlayed = true;
			} else {
				postSummary();
				summarySoundPlayed = false;
			}
		}
	} else if(gameState == GameState::LoginPrompt) {

	} else if(gameState == GameState::PostGame) {
		if(not speechInst.getPlaying()) {
			getEngine()->switchToActivity("highscores");
		}
	}
}

void GameActivity::start()
{
	score = 0;

	faggots->removeCock();
	faggots->pos = al::Rect<>::XYWH(160, 100, 480, 400);

	sndCountdown.play();
	setState(GameState::Countdown);
	al::DefaultMixer.attachSampleInstance(speechInst);
}

void GameActivity::stop()
{
	speechInst.detach();
}

bool GameActivity::handleEvent(const ALLEGRO_EVENT &ev)
{
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			getEngine()->switchToActivity("mainmenu");
			return true;
		}

		if(gameState == GameState::Gameplay) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_LCTRL) {
				if(faggots->removeCock()) {
					sndOut.play();
				}
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_RCTRL) {
				if(int pts = faggots->insertCock()) {
					score += pts;
					spawnUnique<PointsInfo>(pts, al::Vec2f{380, 350})->zIndex = 90;
					sndIn.play({.gain = 0.4});
				}
			}
		}

		if(gameState == GameState::LoginPrompt && loginInput.size()>0 && ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			auto& hs = Highscores::getInstance();
			hs.saveScore(loginStrClean(), score);
			sndJingle.play();
			endGame();
		}

	}

	if(ev.type == ALLEGRO_EVENT_KEY_CHAR && gameState == GameState::LoginPrompt) {
		if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			if(not loginInput.empty()) {
				loginInput.pop_back();
			}
		} else if(loginInput.size() < 5) {
			if(std::isalnum(ev.keyboard.unichar)) {
				loginInput += (char32_t)std::toupper(ev.keyboard.unichar);
			}
		}
	}

	return false;
}

void GameActivity::setState(GameActivity::GameState gameState1)
{
	gameState = gameState1;
	lastStateChange = al::GetTime();
}

void GameActivity::preRender()
{
	auto& font = getEngine()->font();
	font.draw(al::Format("Czas: %.2f", timeLeft), al::PureGreen, {20, 530});
	font.draw(al::Format("Wynik: %d", score), al::PureGreen, {20, 560});
	font.draw("sterowanie: LCTRL/RCTRL", al::PureGreen, {10, 10});


	if(gameState == GameState::Countdown) {
		int val = 3;
		if(timeSinceStart() > 0.51) {
			val = 2;
		}
		if(timeSinceStart() > 0.91) {
			val = 1;
		}
		font.draw(std::to_string(val), al::PureGreen, {400, 100});
	}
}

void GameActivity::postRender()
{
	auto& font = getEngine()->font();
	if(gameState == GameState::LoginPrompt) {
		al::DrawFilledRectangle(al::CurrentDisplay.rect(), al::RGBA_f(0,0,0,0.7));
		font.draw("LOGIN:", al::PureGreen, {400, 270}, ALLEGRO_ALIGN_CENTER);
		font.draw(loginStr(), al::PureGreen, {400, 300}, ALLEGRO_ALIGN_CENTER);
	}

}

double GameActivity::timeSinceStateChange() const
{
	return al::GetTime() - lastStateChange;
}

void GameActivity::playSummarySound()
{
	auto& hs = Highscores::getInstance();
	if(hs.isTopScore(score)) {
		speechInst.setSample(sndHighScore);
	} else {
		speechInst.setSample(sndLowScore);
	}
	speechInst.setPosition(0);
	speechInst.setPlaying(true);
}

std::string GameActivity::loginStr() const
{
	std::u32string ret32;
	for(int i=0; i<5; i++) {
		if(i < loginInput.size()) {
			ret32 += loginInput[i];
		} else {
			ret32 += '*';
		}
	}
	return al::ToUTF8(ret32);
}

void GameActivity::postSummary()
{
	auto& hs = Highscores::getInstance();
	if(hs.isScoreEligible(score)) {
		setState(GameState::LoginPrompt);
		speechInst.setSample(sndLoginPrompt);
		speechInst.setPlaying(true);
	} else {
		endGame();
	}
}

std::string GameActivity::loginStrClean() const
{
	auto ret = loginStr();
	while(!ret.empty() && ret.back() == '*') {
		ret.pop_back();
	}
	return ret;
}

void GameActivity::endGame()
{
	speechInst.setSample(sndUnsat);
	speechInst.setPlaying(true);
	setState(GameState::PostGame);
}
