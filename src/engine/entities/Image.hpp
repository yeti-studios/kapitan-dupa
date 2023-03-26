//
// Created by volt on 2023-02-20.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_IMAGE_HPP
#define KPTDUPA_IMAGE_HPP

#include "SpatialEntity.hpp"


class Image: public SpatialEntity {
protected:
	std::shared_ptr<al::Bitmap> bitmap;
	std::optional<std::string> filename;
public:
	al::Color tint = al::White;

	explicit Image(const std::shared_ptr<al::Bitmap> &bitmap);
	explicit Image(const std::string& imgPath);
	Image() = default;

	void unload();

	const al::Bitmap* bmp() const;

	void render() override;
	void update() override;
	void handle(const ALLEGRO_EVENT &ev) override;
};


#endif //KPTDUPA_IMAGE_HPP
