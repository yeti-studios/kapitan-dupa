//
// Created by volt on 2023-03-03.
//

#include "../engine/all.hpp"

#ifndef KPTDUPA_SCROLLINGIMAGE_HPP
#define KPTDUPA_SCROLLINGIMAGE_HPP

class ScrollingImage: public Image {
	using Image::Image;
public:
	void setProgress(float progress1);
	float progress = 0.0;
	bool vertical = false;
	void render() override;
};


#endif //KPTDUPA_SCROLLINGIMAGE_HPP
