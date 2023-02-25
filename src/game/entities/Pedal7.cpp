//
// Created by volt on 2023-02-20.
//

#include "Pedal7.hpp"

#include <cmath>
#include <axxegro/axxegro.hpp>

void Pedal7::update()
{

}

void Pedal7::render()
{
	static std::array<al::Bitmap, 4> frames = {
			al::Bitmap("res/img/pedal7/frm0.png"),
			al::Bitmap("res/img/pedal7/frm1.png"),
			al::Bitmap("res/img/pedal7/frm2.png"),
			al::Bitmap("res/img/pedal7/frm3.png")
	};

	[[maybe_unused]] double chuj;
	double frac = std::modf(al::GetTime() * 2.5, &chuj);
	al::Bitmap& currentFrame = frames.at(int(frac*4));

	currentFrame.drawScaled(currentFrame.rect(), this->rect);
}

void Pedal7::handle(const ALLEGRO_EVENT &ev)
{

}

Pedal7::Pedal7(al::Rect<float> rect)
{
	this->rect = rect;
}
