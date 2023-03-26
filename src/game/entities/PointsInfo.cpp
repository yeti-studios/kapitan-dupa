//
// Created by volt on 2023-03-04.
//

#include "PointsInfo.hpp"

void PointsInfo::update()
{
	if(timeSinceSpawn() > 2.0) {
		kill();
	}
}

void PointsInfo::render()
{
	al::Vec2f actualPos = pos + dir*timeSinceSpawn();

	auto& font = getEngine()->font();

	std::string text = al::Format("+%d", points);
	float green = std::clamp<float>(std::atan(points / 800.0) / M_PI_2, 0.3f, 1.0f);
	float red = std::clamp<float>(std::atan(points / 3000.0) / M_PI_2, 0.0f, 1.0f);
	al::Color col = al::RGB_f(red, green, 0);

	for(int i=0; i<9; i++) {
		al::Vec2f off(-1 + (i%3), -1 + (i/3));
		off *= 2;
		font.draw(text, al::Black, actualPos + off, ALLEGRO_ALIGN_CENTER);
	}
	font.draw(text, col, actualPos, ALLEGRO_ALIGN_CENTER);

}

void PointsInfo::handle(const ALLEGRO_EVENT &ev)
{

}

PointsInfo::PointsInfo(int points, al::Vec2f pos)
	: points(points), pos(pos)
{
	dir = -al::Vec2f(RandDouble() * 100 - 50, 300);
}
