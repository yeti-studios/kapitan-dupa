//
// Created by volt on 2023-02-25.
//

#include <kptdup_pch.hpp>

#ifndef KPTDUPA_BUTTON_HPP
#define KPTDUPA_BUTTON_HPP

#include "../../engine/entities/SpatialEntity.hpp"

class Button: public SpatialEntity {
public:
	std::function<void(void)> onclick = [](){};

	explicit Button(std::string text, al::Rect<> rect = {0, 0, 100, 30});
	std::string text;

	void update() override;
	void render() override;
	void handle(const ALLEGRO_EVENT &ev) override;
private:
	int hoverState = 0;
	int prevHoverState = 0;
};


#endif //KPTDUPA_BUTTON_HPP
