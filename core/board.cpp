#include "core/board.h"
#include "managers/entity_manager.h"

std::array<std::vector<size_t>, board::cols_n * board::rows_n> board::fields_;
const size_t board::empty_id;

void board::prepare_board()
{
	//std::fill(std::begin(fields_), std::end(fields_), empty_id);

	entity_manager::on_destroy([](size_t entity_id)
	{
		auto it = std::find_if(std::begin(fields_), std::end(fields_), [entity_id](auto field){
			if (field.empty())
				return false;
			return field.back() == entity_id;
		});
		it->pop_back();
	});
}