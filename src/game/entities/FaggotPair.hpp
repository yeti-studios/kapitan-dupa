//
// Created by volt on 2023-02-20.
//

#ifndef KPTDUPA_FAGGOTPAIR_HPP
#define KPTDUPA_FAGGOTPAIR_HPP

#include "../../engine/Entity.hpp"

class FaggotPair: public Entity {
	void render() override;
	void update() override;
	void handle(const ALLEGRO_EVENT &ev) override;
};


#endif //KPTDUPA_FAGGOTPAIR_HPP
