//
// Created by volt on 2023-02-20.
//

#include "Pedal7.hpp"

void Pedal7::update()
{
	static std::array<std::shared_ptr<al::Bitmap>, 4> frames = {
			std::make_shared<al::Bitmap>("res/img/pedal7/frm0.png"),
			std::make_shared<al::Bitmap>("res/img/pedal7/frm1.png"),
			std::make_shared<al::Bitmap>("res/img/pedal7/frm2.png"),
			std::make_shared<al::Bitmap>("res/img/pedal7/frm3.png")
	};

	[[maybe_unused]] double chuj;
	double frac = std::modf(al::GetTime() * 2.5, &chuj);
	this->bitmap = frames.at(int(frac*4));
}
