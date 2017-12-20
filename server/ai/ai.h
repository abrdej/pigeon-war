#ifndef AI_H
#define AI_H

#include "core/players.h"
#include "behavior_tree.h"

class board;
class entity_manager;
class path_finder;

namespace ai
{
	class ai_brain
	{
	public:
		ai_brain(const players::player_id_type& player_name);
		void do_turn();
	private:
		void move_entity(size_t entity_index);
		//bool attack_if_can(size_t from_index, size_t on_index);
		//void go_in_direction(size_t from_index, size_t to_index);
	private:
		const players::player_id_type& player_name_;
	};

	namespace behavior_tree_tasks
	{
		struct blackboard
		{
			blackboard(const std::string& player_name, size_t entity_index)
				: player_name_(player_name),
				my_entity_index_(entity_index),
				nearest_enemy_index(-1),
				destination_index(-1)
			{
			}
			std::string player_name_;
			size_t my_entity_index_;
			size_t nearest_enemy_index;
			size_t destination_index;
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
	}
};

#endif