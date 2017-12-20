#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <vector>
#include <memory>

namespace behavior_tree
{
	template <typename BlackBoard>
	class base_task
	{
	public:
		virtual bool operator()(BlackBoard& blackboard) = 0;
	};

	template <typename BlackBoard>
	class branch_task : public base_task<BlackBoard>
	{
	public:
		virtual bool operator()(BlackBoard& blackboard) = 0;
		std::vector<std::shared_ptr<base_task<BlackBoard>>>& get_tasks()
		{
			return tasks;
		}
		void add_task(const std::shared_ptr<base_task<BlackBoard>>& task)
		{
			tasks.push_back(task);
		}
	private:
		std::vector<std::shared_ptr<base_task<BlackBoard>>> tasks;
	};

	template <typename BlackBoard>
	class selector : public branch_task<BlackBoard>
	{
	public:
		virtual bool operator()(BlackBoard& blackboard) override
		{
			for (auto it = std::begin(branch_task<BlackBoard>::get_tasks());
				 it != std::end(branch_task<BlackBoard>::get_tasks());
				 ++it)
				if ((**it)(blackboard))
					return true;
			return false;
		}
	};

	template <typename BlackBoard>
	class sequence : public branch_task<BlackBoard>
	{
	public:
		virtual bool operator()(BlackBoard& blackboard) override
		{
			for (auto it = std::begin(branch_task<BlackBoard>::get_tasks());
				 it != std::end(branch_task<BlackBoard>::get_tasks());
				 ++it)
				if (!(**it)(blackboard))
					return false;
			return true;
		}
	};

	namespace helper
	{
		template <typename... Types>
		struct constructor_helper_impl;

		template <typename BranchTask, typename Task1, typename... Tasks>
		struct constructor_helper_impl<BranchTask, Task1, Tasks...>
		{
			void operator()(BranchTask& branch_task)
			{
				constructor_helper_impl<BranchTask, Tasks...> construct_helper;
				construct_helper(branch_task);
				branch_task.add_task(std::make_shared<Task1>());
			}
		};

		template <typename BranchTask, typename Task1>
		struct constructor_helper_impl<BranchTask, Task1>
		{
			void operator()(BranchTask& branch_task)
			{
				branch_task.add_task(std::make_shared<Task1>());
			}
		};

		template <typename BranchTask, typename... Tasks>
		void constructor_helper(BranchTask& branch_task)
		{
			constructor_helper_impl<BranchTask, Tasks...> constructor;
			constructor(branch_task);
		}

		template <typename BlackBoard, typename... Tasks>
		class Sequence : public sequence<BlackBoard>
		{
		protected:
			Sequence()
			{
				constructor_helper<sequence<BlackBoard>, Tasks...>(*this);
			}
		public:
			static std::shared_ptr<sequence<BlackBoard>> create()
			{
				return std::shared_ptr<Sequence>(new Sequence());
			}
		};
	}
}

#endif