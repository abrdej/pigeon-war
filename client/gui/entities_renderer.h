//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ENTITIES_RENDERER_H
#define PIGEONWAR_ENTITIES_RENDERER_H

#include <SFML/Graphics.hpp>
#include "drawing_manager.h"
#include "client/board_container.h"

struct entities_renderer {
	void render(sf::RenderWindow& window, board_container& board, const std::unordered_map<sf::Uint64, sf::Int32>& healths) {

		board.for_each([this, &healths, &window](sf::Uint64 entity_id, sf::Uint64 col, sf::Uint64 row) {
			if (entity_id != -1) {
				drawing_manager::drawer_for(entity_id)->draw(window, col, row, healths.at(entity_id));
			}
		});
	}
};

#endif //PIGEONWAR_ENTITIES_RENDERER_H
