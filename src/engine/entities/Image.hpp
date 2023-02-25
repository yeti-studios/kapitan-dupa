//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_IMAGE_HPP
#define KPTDUPA_IMAGE_HPP

#include "SpatialEntity.hpp"

#include "axxegro/axxegro.hpp"

#include <optional>

class Image: public SpatialEntity {
	std::shared_ptr<al::Bitmap> bitmap;
public:
	explicit Image(const std::shared_ptr<al::Bitmap> &bitmap);
	explicit Image(const std::string& imgPath);

	void render() override;
};


#endif //KPTDUPA_IMAGE_HPP
