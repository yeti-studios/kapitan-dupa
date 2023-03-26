//
// Created by volt on 2023-02-20.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_SPATIALENTITY_HPP
#define KPTDUPA_SPATIALENTITY_HPP

#include "../Entity.hpp"

class SpatialEntity: public Entity
{
public:
	[[nodiscard]] al::Rect<float>& rect();
	void setRect(al::Rect<float> rect);

	[[nodiscard]] al::Vec2f getPos() const;
	[[nodiscard]] al::Vec2f getSize() const;

	void setCenter(al::Vec2f pos);
private:
	al::Rect<float> rect_;
};

#endif //KPTDUPA_SPATIALENTITY_HPP
