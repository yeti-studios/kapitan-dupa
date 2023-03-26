//
// Created by volt on 2023-03-03.
//

#include "ScrollingImage.hpp"

void ScrollingImage::render()
{
	setRect(al::CurrentDisplay.rect());
	al::Vec2f dp = al::CurrentDisplay.size().hadamard(vertical ? al::Vec2i(0,1) : al::Vec2i(1,0));

	for(int i=0; i<2; i++) {
		float coeff = progress - float(i);
		al::Transform tx;
		tx.translate(dp * coeff);
		al::ScopedTransform stx(tx);
		Image::render();
	}
}

void ScrollingImage::setProgress(float progress1)
{
	float fuckOff;
	progress = std::modf(progress1, &fuckOff);
}
