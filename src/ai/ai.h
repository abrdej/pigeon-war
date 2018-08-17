#ifndef AI_H
#define AI_H

#include <managers/players_manager.h>
#include <ai/behavior_tree.h>
#include <boost/any.hpp>

class board;
class entity_manager;
class path_finder;

namespace ai
{

namespace behavior_tree_tasks
{

namespace entry_tag {
struct player_id{};
struct my_entity_index_{};
struct nearest_enemy_index{};
struct destination_index{};
}

template <typename Tag>
struct entry_traits {
	using value_type = std::uint32_t;
};

template <typename Tag>
using tag_type = typename entry_traits<Tag>::value_type;

template <typename Tag>
inline auto entry_construct_default() {
	return tag_type<Tag>{};
}

template <>
inline auto entry_construct_default<entry_tag::nearest_enemy_index>() {
	return std::numeric_limits<std::uint32_t>::max();
}

template <>
inline auto entry_construct_default<entry_tag::destination_index>() {
	return std::numeric_limits<std::uint32_t>::max();
}

struct blackboard
{
	template <typename EntryTag>
	tag_type<EntryTag>& entry() {
		auto it = entries.find(typeid(EntryTag));
		if (it == std::end(entries)) {
			it = entries.emplace(typeid(EntryTag), entry_construct_default<EntryTag>()).first;
		}
		return boost::any_cast<tag_type<EntryTag>&>(it->second);
	}
	template <typename EntryTag>
	bool entry(tag_type<EntryTag>& x) {
		auto it = entries.find(typeid(EntryTag));
		return (it != std::end(entries) && (x = boost::any_cast<tag_type<EntryTag>&>(it->second), true));
	}
	template <typename EntryTag>
	void set_entry(const tag_type<EntryTag>& x) {
		entries.emplace(typeid(EntryTag), x);
	}
	std::unordered_map<std::type_index, boost::any> entries;
};

template <typename TaskType>
std::shared_ptr<TaskType> make_task()
{
	return std::make_shared<TaskType>();
}

struct find_nearest_enemy : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct attack_enemy : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct go_close_to : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct find_position_for_shot : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct go_to : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct can_go_to : behavior_tree::base_task<blackboard> {
	bool operator()(blackboard& blackboard) override;
};

struct find_best_aim : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

struct find_best_aim_for_golem : behavior_tree::base_task<blackboard>
{
	bool operator()(blackboard& blackboard) override;
};

class run_around : public behavior_tree::base_task<blackboard> {
public:
	run_around();
	bool operator()(blackboard& blackboard) override;
private:
	std::vector<std::pair<std::int32_t, std::int32_t>> shifts;
	std::size_t shift_index;
};

}
}

#endif