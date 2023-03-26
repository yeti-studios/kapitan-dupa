//
// Created by volt on 2023-03-03.
//
#include <kptdup_pch.hpp>

#include "Math.hpp"

std::random_device rd;
std::mt19937_64 gen {rd()};

double RandDouble()
{
	static std::uniform_real_distribution<double> dist;
	return dist(gen);
}



al::Vec2f RandVec2()
{
	return al::Vec2d {RandDouble(), RandDouble()};
}

int RandInt(int val)
{
	static std::uniform_int_distribution<int> dist(0, val-1);
	return dist(gen);
}
