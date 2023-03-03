//
// Created by volt on 2023-02-25.
//

#include "Button.hpp"
#include "../engine/Engine.hpp"
#include "../engine/Activity.hpp"

void Button::update()
{
	static al::Sample btnHover {"res/sfx/btn_hover.wav"};

	prevHoverState = hoverState;
	hoverState = rect().contains(al::GetMousePos());

	if(hoverState - prevHoverState == 1) {
		btnHover.play();
	}
}

void Button::render()
{
	al::DrawFilledRoundRect(rect(), {7, 7}, al::RGB(0, 0, 50 + 30 * hoverState));
	al::DrawRoundRect(rect(), {7, 7}, al::RGB(0, 0, 255));

	al::Vec2f center = rect().center();
	auto& font = getEngine()->font();

	font.draw(text, al::PureGreen, center - al::Vec2f {0.f, (float)font.getLineHeight()/2.0f}, ALLEGRO_ALIGN_CENTER);

}

void Button::handle(const ALLEGRO_EVENT &ev)
{
	static al::Sample btnClick {"res/sfx/btn_click.wav"};
	if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if(hoverState && ev.mouse.button == al::LMB) {
			btnClick.play();
			onclick();
		}
	}
}

Button::Button(std::string text, al::Rect<> rect)
	: text(std::move(text))
{
	setRect(rect);
}
