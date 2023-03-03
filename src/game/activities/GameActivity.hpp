//
// Created by volt on 2023-02-20.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_GAMEACTIVITY_HPP
#define KPTDUPA_GAMEACTIVITY_HPP

#include "../../engine/all.hpp"

class GameActivity: public Activity {
public:
	void init() override;

	void tick() override;

	void start() override;

	void stop() override;

	bool handleEvent(const ALLEGRO_EVENT &ev) override;
};


#endif //KPTDUPA_GAMEACTIVITY_HPP
