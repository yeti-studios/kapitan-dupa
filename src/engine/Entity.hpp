//
// Created by volt on 2023-02-18.
//

#ifndef KPTDUPA_ENTITY_HPP
#define KPTDUPA_ENTITY_HPP

#include <kptdup_pch.hpp>

class Activity;
class Engine;

class Entity {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handle(const ALLEGRO_EVENT& ev) = 0;

	virtual ~Entity() = default;

	int zIndex = 0;

	Activity* getActivity() const;
	Engine* getEngine() const;
private:
	friend class Activity;
	Activity* activity;
	void setActivity(Activity* activity1);

};


#endif //KPTDUPA_ENTITY_HPP
