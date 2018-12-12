#pragma once

#include <cstdint>

#include <core/turn_system.h>

struct effect {
	virtual bool set_effect(std::uint32_t entity_id) = 0;
	virtual void remove_effect(std::uint32_t entity_id) = 0;
};

struct base_effect {
	virtual ~base_effect() = default;
};

enum class effect_types {
	positive,
	negative
};

class applied_effect {
private:
	std::string name;
	std::string description;
	effect_types effect_type{effect_types::negative};
	bool effect_removable{false};
    turn_scoped_connection turn_connection;
    std::function<void()> on_destruction{nullptr};

public:
    applied_effect() = default;

    ~applied_effect() {
        if (on_destruction)
            on_destruction();
    }

	std::string get_name() const {
		return name;
	}
	std::string get_description() const {
		return description;
	}
	effect_types get_effect_type() const {
		return effect_type;
	}
    bool is_effect_removable() const {
		return effect_removable;
	}
    void set_turn_connection(turn_scoped_connection connection) {
        turn_connection = std::move(connection);
    }
    template <typename Callback>
    void set_on_destruction(Callback callback) {
        on_destruction = callback;
    }

    friend std::shared_ptr<applied_effect> make_negative_effect(const std::string&);
	friend std::shared_ptr<applied_effect> make_positive_effect(const std::string&);
	friend std::shared_ptr<applied_effect> make_not_removable_negative_effect(const std::string&);
    friend std::shared_ptr<applied_effect> make_not_removable_positive_effect(const std::string&);
};

inline std::shared_ptr<applied_effect> make_negative_effect(const std::string& name) {
    auto effect = std::make_shared<applied_effect>();
    effect->name = name;
    effect->effect_removable = true;
    effect->effect_type = effect_types::negative;
    return effect;
}

inline std::shared_ptr<applied_effect> make_positive_effect(const std::string& name) {
	auto effect = std::make_shared<applied_effect>();
	effect->name = name;
	effect->effect_removable = true;
	effect->effect_type = effect_types::positive;
	return effect;
}

inline std::shared_ptr<applied_effect> make_not_removable_positive_effect(const std::string& name) {
    auto effect = std::make_shared<applied_effect>();
    effect->name = name;
    effect->effect_removable = false;
    effect->effect_type = effect_types::positive;
    return effect;
}

inline std::shared_ptr<applied_effect> make_not_removable_negative_effect(const std::string& name) {
	auto effect = std::make_shared<applied_effect>();
	effect->name = name;
	effect->effect_removable = false;
	effect->effect_type = effect_types::negative;
	return effect;
}
