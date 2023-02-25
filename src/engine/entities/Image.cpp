//
// Created by volt on 2023-02-20.
//

#include "Image.hpp"

void Image::render()
{
	bitmap->drawScaled(bitmap->rect(), this->rect);
}

Image::Image(const std::shared_ptr<al::Bitmap> &bitmap)
	: bitmap(bitmap)
{
	rect = bitmap->rect();
}

Image::Image(const std::string &imgPath)
	: bitmap(std::make_shared<al::Bitmap>(imgPath))
{
	rect = bitmap->rect();
}
