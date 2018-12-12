#pragma once

#include <vector>

#include <ai/behavior_node.h>

namespace ai {

class branch_node : public behavior_node {
public:
    void add_node(behavior_node_ptr node) {
        nodes_.push_back(std::move(node));
    }
protected:
    std::vector<behavior_node_ptr> nodes_;
};

struct selector_node : branch_node {
    bool operator()(ai_knowledge& knowledge) override {
        for (auto& node : nodes_)
            if ((*node)(knowledge)) return true;
        return false;
    }
};

struct sequence_node : branch_node {
    bool operator()(ai_knowledge& knowledge) override {
        for (auto& node : nodes_)
            if (!(*node)(knowledge)) return false;
        return true;
    }
};

using branch_ptr = std::shared_ptr<branch_node>;
using selector_ptr = std::shared_ptr<selector_node>;
using sequence_ptr = std::shared_ptr<sequence_node>;

template <typename Node>
using node_ptr = std::shared_ptr<Node>;

namespace construct {
namespace detail {
inline void apply_node_to_branch(branch_node& branch, behavior_node_ptr node) {
    branch.add_node(std::move(node));
};

template <typename... Nodes>
inline void apply_nodes_to_branch(branch_node& branch, node_ptr<Nodes>... nodes) {
    int apply[] = {(apply_node_to_branch(branch, std::move(nodes)), 0)...};
    (void)apply;
};
} // namespace detail

template <typename Type, typename... Args>
const auto make_node = std::make_shared<Type, Args...>;

template <typename... Nodes>
behavior_node_ptr make_sequence(node_ptr<Nodes>... nodes) {
    auto sequence = std::make_shared<sequence_node>();
    detail::apply_nodes_to_branch(*sequence, std::move(nodes)...);
    return sequence;
}

template <typename... Nodes>
behavior_node_ptr make_selector(node_ptr<Nodes>... nodes) {
    auto selector = std::make_shared<selector_node>();
    detail::apply_nodes_to_branch(*selector, std::move(nodes)...);
    return selector;
}

} // namespace construct
} // namespace ai
