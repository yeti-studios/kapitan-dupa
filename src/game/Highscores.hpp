//
// Created by volt on 2023-03-04.
//

#include <kptdup_pch.hpp>

#ifndef KPTDUPA_HIGHSCORES_HPP
#define KPTDUPA_HIGHSCORES_HPP

struct Highscore {
	std::string login;
	int score;
};

class Highscores {
public:
	explicit Highscores(const std::string& filename);
	~Highscores();

	static Highscores& getInstance();

	bool isTopScore(int score) const;
	bool isScoreEligible(int score) const;
	void saveScore(const std::string& name, int score);

	void saveToDisk();

	[[nodiscard]] const std::vector<Highscore> & getHighscores() const;

	static constexpr int MaxHighscores = 10;
private:
	void update();
	std::string filename;
	std::vector<Highscore> scores;
};


#endif //KPTDUPA_HIGHSCORES_HPP
