//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_FAGGOTPAIR_HPP
#define KPTDUPA_FAGGOTPAIR_HPP

#include "../../engine/Entity.hpp"

class FaggotPair: public Entity {
	std::shared_ptr<al::Bitmap> img1, img2;
public:
	FaggotPair(std::shared_ptr<al::Bitmap> img1, std::shared_ptr<al::Bitmap> img2);
	al::Rect<> pos;
	int state = 0;
	double lastCockInsertion = 0.0;

	int insertCock();
	int removeCock();

	static int calcPoints(double interval);

	void render() override;
	void update() override;
	void handle(const ALLEGRO_EVENT &ev) override;
};


#endif //KPTDUPA_FAGGOTPAIR_HPP
