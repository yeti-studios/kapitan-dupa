//
// Created by volt on 2023-03-04.
//

#include "../engine/all.hpp"

#ifndef KPTDUPA_POINTSINFO_HPP
#define KPTDUPA_POINTSINFO_HPP

class PointsInfo: public Entity {
public:
	PointsInfo(int points, al::Vec2f pos);

	void update() override;
	void render() override;
	void handle(const ALLEGRO_EVENT &ev) override;
private:

	int points;
	al::Vec2f pos;
	al::Vec2f dir;
};


#endif //KPTDUPA_POINTSINFO_HPP
