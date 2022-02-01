#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"
#include "Structs.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		Slot slots[Constants::NumberOfScores];

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			
			for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {
				slots[i].reset();
				slots[i].score = 5 - i;
			}

			this->saveCookie();

		}

};