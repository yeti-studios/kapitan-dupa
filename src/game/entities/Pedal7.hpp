//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_PEDAL7_HPP
#define KPTDUPA_PEDAL7_HPP


#include "../../engine/entities/SpatialEntity.hpp"
#include "axxegro/resources/Bitmap.hpp"

class Pedal7: public SpatialEntity {
public:
	explicit Pedal7(al::Rect<float> rect = al::Rect<float>::PosSize({390, 80}, {360, 145}));

	void update() override;
	void render() override;
	void handle(const ALLEGRO_EVENT& ev) override;

private:

};


#endif //KPTDUPA_PEDAL7_HPP
