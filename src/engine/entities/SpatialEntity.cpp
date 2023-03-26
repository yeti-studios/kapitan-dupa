//
// Created by volt on 2023-02-20.
//

#include "SpatialEntity.hpp"

al::Vec2f SpatialEntity::getPos() const
{
	return rect_.a;
}

al::Vec2f SpatialEntity::getSize() const
{
	return rect_.size();
}

al::Rect<float>& SpatialEntity::rect()
{
	return rect_;
}

void SpatialEntity::setRect(al::Rect<float> rect)
{
	rect_ = rect;
}

void SpatialEntity::setCenter(al::Vec2f pos)
{
	auto currentCenter = rect_.center();
	rect_ += pos - currentCenter;
}

