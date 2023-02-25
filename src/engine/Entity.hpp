//
// Created by volt on 2023-02-18.
//

#ifndef KPTDUPA_ENTITY_HPP
#define KPTDUPA_ENTITY_HPP

#include <axxegro/event/EventQueue.hpp>

class Entity {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handle(const ALLEGRO_EVENT& ev) = 0;

	virtual ~Entity() = default;

	int zIndex = 0;
private:

};


#endif //KPTDUPA_ENTITY_HPP
