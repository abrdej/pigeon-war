#ifndef AI_H
#define AI_H

#include "managers/players_manager.h"
#include "behavior_tree.h"

class board;
class entity_manager;
class path_finder;

namespace ai
{
class ai_brain
{
public:
	explicit ai_brain(sf::Uint64 player_id);
	void do_turn();
private:
	void move_entity(sf::Uint64 entity_index);
	//bool attack_if_can(sf::Uint64 from_index, sf::Uint64 on_index);
	//void go_in_direction(sf::Uint64 from_index, sf::Uint64 to_index);
private:
	const sf::Uint64 player_id;
};

namespace behavior_tree_tasks
{
struct blackboard
{
	blackboard(sf::Uint64 player_id,
			   sf::Uint64 entity_index)
			: player_id(player_id),
			  my_entity_index_(entity_index),
			  nearest_enemy_index(-1),
			  destination_index(-1)
	{
	}
	sf::Uint64 player_id;
	sf::Uint64 my_entity_index_;
	sf::Uint64 nearest_enemy_index;
	sf::Uint64 destination_index;
};

template <typename TaskType>
std::shared_ptr<TaskType> make_task()
{
	return std::make_shared<TaskType>();
}

class find_nearest_enemy : public behavior_tree::base_task<blackboard>
{
public:
	virtual bool operator()(blackboard& blackboard) override;
};

class attack_enemy : public behavior_tree::base_task<blackboard>
{
public:
	virtual bool operator()(blackboard& blackboard) override;
};

class go_close_to : public behavior_tree::base_task<blackboard>
{
public:
	virtual bool operator()(blackboard& blackboard) override;
};

class find_position_for_shot : public behavior_tree::base_task<blackboard>
{
public:
	virtual bool operator()(blackboard& blackboard) override;
};

class go_to : public behavior_tree::base_task<blackboard>
{
public:
	virtual bool operator()(blackboard& blackboard) override;
};

struct can_go_to : public behavior_tree::base_task<blackboard> {
	bool operator()(blackboard& blackboard) override;
};

struct find_best_aim : public behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

}
};

#endif