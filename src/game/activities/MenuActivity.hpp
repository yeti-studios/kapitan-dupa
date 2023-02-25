//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_MENUACTIVITY_HPP
#define KPTDUPA_MENUACTIVITY_HPP

#include "../../engine/Activity.hpp"

class MenuActivity: public Activity {
public:
	MenuActivity();

	void init() override;
	void tick() override;

	void start() override;
	void stop() override;
private:
	al::AudioStream menuMusic;
};


#endif //KPTDUPA_MENUACTIVITY_HPP
