//
// Created by volt on 2023-02-25.
//

#include <kptdup_pch.hpp>

#ifndef KPTDUPA_STARBACKGROUND_HPP
#define KPTDUPA_STARBACKGROUND_HPP


#include "../../engine/Entity.hpp"

class StarBackground: public Entity {

	std::vector<al::Vec2f> starPattern[2];
	std::unique_ptr<al::VertexBuffer> starPatternMesh[2];

public:
	StarBackground();

	void update() override;
	void render() override;
	void handle(const ALLEGRO_EVENT &ev) override;
};


#endif //KPTDUPA_STARBACKGROUND_HPP
