#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <core/game_state.h>
#include "board.h"
#include "module_holder.h"
#include "managers/players_manager.h"
#include <memory>

class game
{
public:
	game();
	void on_board(std::uint32_t col, std::uint32_t row);
	void on_button(std::uint32_t n);
	std::string get_button_description(std::uint32_t selected_index, std::uint32_t n);

	void defeat();
	void victory();

    static std::unordered_map<std::type_index, std::shared_ptr<void>> systems;

    template <typename System>
    static System& get() {
		auto it = systems.find(typeid(System));
		if (it == std::end(systems)) {
			it = systems.emplace(typeid(System), std::make_shared<System>()).first;
		}
		return *std::static_pointer_cast<System>(it->second);
    }

	static game& get_instance() {
		static game game;
		return game;
	}
};



#endif