//
// Created by volt on 2023-02-20.
//

#include "FaggotPair.hpp"

void FaggotPair::render()
{
	std::shared_ptr<al::Bitmap>& src = state ? img2 : img1;
	src->drawScaled(src->rect(), pos);
}

void FaggotPair::update()
{

}

void FaggotPair::handle(const ALLEGRO_EVENT &ev)
{

}

FaggotPair::FaggotPair(std::shared_ptr<al::Bitmap> img1, std::shared_ptr<al::Bitmap> img2)
	: img1(std::move(img1)), img2(std::move(img2))
{

}

int FaggotPair::insertCock()
{
	if(state == 0) {
		double t = al::GetTime();
		double interval = t - lastCockInsertion;
		lastCockInsertion = t;
		state = 1;
		return calcPoints(interval);
	}
	return 0;
}

int FaggotPair::removeCock()
{
	if(state == 1) {
		state = 0;
		return 1;
	}
	return 0;
}

int FaggotPair::calcPoints(double interval)
{
	interval = std::max(0.01, interval);
	int val = int(std::pow(20.0 / interval, 3.0)) / 1000;
	val -= val%10;
	return val;
}
