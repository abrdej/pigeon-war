#include "skirmish.h"

#include <config.h>
#include <entities/entities_factory.h>
#include <scenarios/creator_helper.h>
#include <scenarios/entities_reader.h>
#include <scenarios/map_reader.h>
#include <scenarios/registered_entities.h>

using creator_helper::pos;

template <typename T>
void create_around_map() {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> trees_positions;
    for (std::int32_t i = 0; i < game_board().cols_n; ++i) {
        for (std::int32_t j = 0; j < game_board().rows_n; ++j) {
            if (i == 0 || j == 0 || i == game_board().cols_n - 1|| j == game_board().rows_n - 1) {
                trees_positions.push_back(pos(i, j));
            }
        }
    }
    creator_helper::create_neutral_many<T>(trees_positions);
}

void winter_land() {

    create_around_map<fir>();

    creator_helper::create_neutral_many<fir>({pos(6, 1), pos(7, 1), pos(6, 2), pos(7, 2)});
    creator_helper::create_neutral_many<fir>({pos(10, 1), pos(11, 1), pos(10, 2), pos(11, 2)});
    creator_helper::create_neutral_many<fir>({pos(7, 7), pos(8, 7), pos(7, 8), pos(8, 8)});
    creator_helper::create_neutral_many<fir>({pos(3, 7), pos(4, 7), pos(3, 8), pos(4, 8)});
    creator_helper::create_neutral_many<wall>({pos(4, 4), pos(4, 5)});
    creator_helper::create_neutral_many<wall>({pos(10, 5), pos(10, 6)});
    creator_helper::create_neutral_many<fir>({pos(6, 4), pos(7, 4), pos(6, 5), pos(7, 5)});
}

void battlefield() {

    create_around_map<tree>();

    creator_helper::create_neutral_many<tree>({pos(8, 1), pos(9, 1), pos(10, 1), pos(10, 2)});
    creator_helper::create_neutral_many<tree>({pos(10, 7), pos(11, 7), pos(10, 8), pos(11, 8)});
    creator_helper::create_neutral_many<tree>({pos(3, 1), pos(3, 2), pos(4, 1), pos(4, 2), pos(3, 5), pos(3, 6)});
    creator_helper::create_neutral_many<tree>({pos(5, 8), pos(6, 8)});
    creator_helper::create_neutral_many<stone>({pos(1, 1), pos(4, 5)});
    creator_helper::create_neutral_many<stone>({pos(1, 1), pos(4, 5)});
}

struct map_factory {
    using map_initializer = std::pair<std::string, std::function<void()>>;

    static void initialize(const std::string& map_name) {
        static std::unordered_map<std::string, std::function<void()>> map_initializers = {
                map_initializer("winter land", &winter_land),
                map_initializer("battlefield", &battlefield)
        };
        map_initializers.at(map_name)();
    }
};

//auto get_entities_selecting_positions() {
//    std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = {
//            pos(5, 2),
//            pos(6, 2),
//            pos(7, 2),
//            pos(8, 2),
//            pos(9, 2),
//
//            pos(5, 3),
//            pos(6, 3),
//            pos(7, 3),
//            pos(8, 3),
//            pos(9, 3),
//
//            pos(5, 4),
//            pos(6, 4),
//            pos(7, 4),
//            pos(8, 4),
//            pos(9, 4),
//
//            pos(5, 5),
//            pos(6, 5),
//            pos(7, 5),
//            pos(8, 5),
//            pos(9, 5),
//
//            pos(5, 6),
//            pos(6, 6),
//            pos(7, 6),
//            pos(8, 6),
//            pos(9, 6)
//    };
//    return std::move(positions);
//}

auto get_entities_selecting_positions() {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> positions = {
            pos(5, 2),
            pos(6, 2),
            pos(7, 2),
            pos(8, 2),
            pos(9, 2),

            pos(5, 3),
            pos(9, 3),

            pos(5, 4),
            pos(9, 4),

            pos(5, 5),
            pos(9, 5),

            pos(5, 6),
            pos(6, 6),
            pos(7, 6),
            pos(8, 6),
            pos(9, 6)
    };
    return std::move(positions);
}

auto get_entities_starting_positions() {

    std::array<std::pair<std::uint32_t, std::uint32_t>, 8> positions = {
            pos(2, 2),
            pos(12, 2),
            pos(2, 4),
            pos(12, 4),
            pos(2, 6),
            pos(12, 6),
            pos(2, 8),
            pos(12, 8)
    };
    return std::move(positions);
}

std::vector<std::string> get_possible_to_choose_entities() {
    std::vector<std::string> result = {
            "wretch",
            "wizzard",
            "warrior",
            "troll",
            //"rocket_thrower",
            "eye",
            "spider",
            "soul_hunter",
            "sorcerer",
            "sniper",
            "shooter",
            "samurai_rat",
            "saberhand",
            //"robot",
            "poisoner",
            "native",
            "monk",
            "mechanical_saw",
            //"killer",
            //"handthrower",
            "guardian",
            "grenadier",
            "golem",
            //"gin",
            "reaper",
            "giant",
            "druid",
            "droid",
            //"dragon",
            "destroyer",
            //"creature",
            "commander"
            //"combat_robot"
    };
    return std::move(result);
}

std::string create_skirmish(const std::string& map_name,
                            std::pair<std::uint32_t, std::uint32_t>& map_size) {

    auto name = read_map_from_json(maps_directory + map_name, map_size);

    auto selecting_positions = get_entities_selecting_positions();
    auto starting_positions = get_entities_starting_positions();

    const int number_of_players = 2;

    std::array<std::uint32_t, number_of_players> players{};
    for (auto& player : players) {
        player = game::get<players_manager>().create_human_player("");
    }

    std::uint32_t i = 0;

    std::unordered_set<std::uint32_t> entities_to_choose;

    auto entities = read_entities_from_json(maps_directory + "entities");
    for (auto&& entity_name : entities) {

        auto id = entities_factory::create(entity_name);

        auto pos = selecting_positions[i++];

        if (selecting_positions.size() < i) {
            break;
        }

        game_board().insert(game_board().to_index(pos.first, pos.second), id);
//        game_board().insert(i++, id);
        game::get<players_manager>().add_neutral_entity(id);

        entities_to_choose.insert(id);
    }

    std::int32_t entities_for_player = 4;
    std::int32_t selections = 0;

    auto create_entities_container = [](){
        return std::unordered_map<std::uint32_t, std::vector<std::uint32_t>>();
    };

    set_every_turn_callback(entities_for_player * number_of_players,
                            [=, entities = create_entities_container()](const turn_callback_info& info) mutable {

                                auto pos = starting_positions[selections];
                                auto new_index = game_board().to_index(pos.first, pos.second);

                                auto entity_id = game_board().move(game_control().selected_index_, new_index);
                                sender::send(make_move_entity_message(entity_id,
                                                                      game_control().selected_index_,
                                                                      new_index));

                                entities[players[selections % 2]].push_back(entity_id);

                                game_control().selected_index_ = new_index;

                                entities_to_choose.erase(entity_id);

                                ++selections;

                                if (info.ended) {
                                    for (auto&& entity_to_remove : entities_to_choose) {
                                        game::get<entity_manager>().destroy(entity_to_remove);
                                    }

                                    for (auto&& player_pack : entities) {
                                        for (auto&& id : player_pack.second) {
                                            game::get<players_manager>().add_entity_for_player(player_pack.first, id);
                                        }
                                    }
//                                    for (auto&& player_pack : entities) {
//                                        if_all_die(player_pack.second, [&]() {
//                                            std::cout << player_pack.first << " win!!!\n";
//                                            game.defeat();
//                                        });
//                                    }

                                    entities.clear();
                                }

                            });

    return name;
}