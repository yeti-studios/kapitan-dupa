//
// Created by volt on 2023-02-20.
//

#include "Image.hpp"

void Image::render()
{
	if(bitmap.get()) {
		bitmap->drawTintedScaled(this->tint, bitmap->rect(), this->rect());
	}
}

Image::Image(const std::shared_ptr<al::Bitmap> &bitmap)
	: bitmap(bitmap)
{
	setRect(bitmap->rect());
}

Image::Image(const std::string &imgPath)
	: bitmap(std::make_shared<al::Bitmap>(imgPath))
{
	setRect(bitmap->rect());
}

void Image::update()
{

}

void Image::handle(const ALLEGRO_EVENT &ev)
{

}
