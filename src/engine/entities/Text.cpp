//
// Created by volt on 2023-02-26.
//

#include "Text.hpp"

void Text::update()
{

}

void Text::render()
{
	auto& font = getEngine()->font();

	font.draw(text, color, rect().a - al::Vec2f(0.0f, -(float)font.getLineHeight() / 2.0f), align);
}

void Text::handle(const ALLEGRO_EVENT &ev)
{

}

Text::Text(std::string text, al::Vec2f pos, al::Color color, int align)
	: text(std::move(text)), color(color), align(align)
{
	setRect({pos.x, pos.y, 0, 0});
}

Text::Text()
	: Text("Sample Text", {0, 0}, al::White, ALLEGRO_ALIGN_CENTER)
{

}
