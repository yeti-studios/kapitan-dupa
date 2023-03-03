//
// Created by volt on 2023-02-25.
//

#include "StarBackground.hpp"

double randDouble()
{
	static std::random_device rd;
	static std::mt19937_64 gen {rd()};
	static std::uniform_real_distribution<double> dist;

	return dist(gen);
}

al::Vec2f randVec2()
{
	return al::Vec2d {randDouble(), randDouble()};
}

std::vector<al::Vec2f> randomPointSet(int size, al::Vec2f max)
{
	std::vector<al::Vec2f> ret(size);
	for(int i=0; i<size; i++) {
		ret[i] = randVec2().hadamard(max);
	}
	return ret;
}

al::Vec2f cis(double angle)
{
	return al::Vec2d{std::cos(angle), std::sin(angle)};
}

std::vector<al::Vertex> generatePointSetMesh(const std::vector<al::Vec2f>& vec, float radius, al::Color color)
{
	std::vector<al::Vertex> ret;

	for(auto& point: vec) {

		al::Vertex v[4];
		for(int i=0; i<4; i++) {
			al::Vec2f vt = point + cis(i * (3.1416*2.0*0.25)) * radius;
			v[i] = al::Vertex({vt.x, vt.y, 0}, {}, color);
		}

		for(auto& idx: {0, 1, 2, 0, 2, 3}) {
			ret.push_back(v[idx]);
		}
	}

	return ret;
}

double fractional(double x)
{
	double fuckOff;
	return std::modf(x, &fuckOff);
}


StarBackground::StarBackground()
{
	starPattern[0] = randomPointSet(60, {800, 600});
	starPattern[1] = randomPointSet(160, {800, 600});

	for(int i=0; i<2; i++) {
		auto mesh = generatePointSetMesh(starPattern[i], 2.0 - i, al::LightGray);
		starPatternMesh[i] = std::make_unique<al::VertexBuffer>(mesh);
	}
}

void StarBackground::update()
{

}

void StarBackground::render()
{
	double time = al::GetTime();
	double offset1 = fractional(time * 0.1);
	double offset2 = fractional(time * 0.03);


	al::Transform tr[2] = {
			al::Transform::Eye().translate(al::Vec2f(-800.0f * offset1, 0.0)),
			al::Transform::Eye().translate(al::Vec2f(-800.0f * offset2, 0.0))
	};

	for(int i=0; i<2; i++) {
		for(int p=0; p<2; p++) {
			al::ScopedTransform st(tr[i]);
			al::DrawVertexBuffer(*starPatternMesh[i]);
			tr[i].translate({800.0f, 0.0f});
		}
	}

}

void StarBackground::handle(const ALLEGRO_EVENT &ev)
{

}
