#pragma once

#include <memory>

#include <turn_based/ai/ai_knowledge.h>

namespace ai {

struct behavior_node {
    virtual bool operator()(ai_knowledge& knowledge) = 0;
};

using behavior_node_ptr = std::shared_ptr<behavior_node>;

#define DEFINE_BEHAVIOR_NODE(NAME) \
class NAME : public behavior_node { \
public: \
    bool operator()(ai_knowledge& knowledge) override; \
};

} // namespace ai
