//
// Created by volt on 2023-03-04.
//

#include "Highscores.hpp"

namespace nl = nlohmann;
namespace fs = std::filesystem;

Highscores::Highscores(const std::string &filename)
	: filename(filename)
{
	using namespace nl::literals;
	if(not fs::exists(filename)) {
		std::ofstream xd(filename);
		xd << R"({"scores":[]})"_json.dump(4);
	}

	std::ifstream jsonfile(filename);
	nl::json json = nl::json::parse(jsonfile);

	for(auto& value: json["scores"]) {
		Highscore hs = {
			.login = value["login"].get<std::string>(),
			.score = value["score"].get<int>()
		};
		scores.push_back(hs);
	}
	update();
}

Highscores::~Highscores()
{
	saveToDisk();
}

Highscores &Highscores::getInstance()
{
	static std::unique_ptr<Highscores> instance = std::make_unique<Highscores>("highscores.json");
	return *instance;
}

bool Highscores::isTopScore(int score) const
{
	auto hs = getHighscores();
	if(hs.empty()) {
		return true;
	}
	return score > hs[0].score;
}

bool Highscores::isScoreEligible(int score) const
{
	auto hs = getHighscores();
	if(hs.size() < MaxHighscores) {
		return true;
	}
	return score > hs[MaxHighscores-1].score;
}

void Highscores::saveScore(const std::string &name, int score)
{
	scores.push_back(Highscore{.login = name, .score = score});
	update();
}

void Highscores::saveToDisk()
{
	update();

	nl::json scoreArr = nl::json::array();
	for(const auto& score: scores) {
		scoreArr.push_back({{"login", score.login}, {"score", score.score}});
	}
	std::string output = nl::json::object({{"scores", scoreArr}}).dump(4);
	std::ofstream outfile(filename);
	outfile << output;
}

const std::vector<Highscore>& Highscores::getHighscores() const
{
	return scores;
}

void Highscores::update()
{
	std::sort(scores.begin(), scores.end(), [](const Highscore& a, const Highscore& b){
		return a.score > b.score;
	});
	while(scores.size() > MaxHighscores) {
		scores.pop_back();
	}
}
