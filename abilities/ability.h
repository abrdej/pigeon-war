#ifndef ABILITY_H
#define ABILITY_H

#include <memory>

class board;
class ability : public std::enable_shared_from_this<ability>
{
protected:
	virtual ~ability(){}
public:
	enum class types { moving, attack, helping, passive };
	void operator()(size_t index)
	{
		prepare(index);
	}
	virtual std::string hint() const {
		return "hint";
	}
private:
	virtual void prepare(size_t for_index) = 0;
protected:
	types type_;
};

#endif