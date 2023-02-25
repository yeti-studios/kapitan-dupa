//
// Created by volt on 2023-02-20.
//

#include "SpatialEntity.hpp"

al::Vec2f SpatialEntity::getPos() const
{
	return rect.a;
}

al::Vec2f SpatialEntity::getSize() const
{
	return rect.size();
}
