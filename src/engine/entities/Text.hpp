//
// Created by volt on 2023-02-26.
//

#ifndef KPTDUPA_TEXT_HPP
#define KPTDUPA_TEXT_HPP

#include "../all.hpp"

class Text: public SpatialEntity {
public:
	al::Color color;
	std::string text;
	int align = ALLEGRO_ALIGN_CENTER;

	Text(std::string text, al::Vec2f pos = {0, 0}, al::Color color = al::White, int align = ALLEGRO_ALIGN_CENTER);
	Text();

	void update() override;
	void render() override;
	void handle(const ALLEGRO_EVENT &ev) override;

private:

};


#endif //KPTDUPA_TEXT_HPP
