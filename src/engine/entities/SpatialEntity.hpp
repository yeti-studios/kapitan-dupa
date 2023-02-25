//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_SPATIALENTITY_HPP
#define KPTDUPA_SPATIALENTITY_HPP

#include "axxegro/math/math.hpp"

#include "../Entity.hpp"

class SpatialEntity: public Entity
{
public:
	al::Rect<float> rect;
	[[nodiscard]] al::Vec2f getPos() const;
	[[nodiscard]] al::Vec2f getSize() const;
};

#endif //KPTDUPA_SPATIALENTITY_HPP
