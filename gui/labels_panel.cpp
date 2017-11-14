#include "labels_panel.h"
/*
#include "view_constants.h"


#include "board.h"
#include "entity.h"

namespace view
{
	void labels_panel::prepare(nana::form& fm)
	{
		label_.create(fm, nana::rectangle(constants::top_left_point.x +
			board::cols_n * constants::field_size, 200, 200, 200));

		label_.format(true);
		label_.text_align(nana::align::center, nana::align_v::top);
		label_.bgcolor(nana::color(230, 230, 230));

		label_.caption(L"Turn based-stwolfegy");
	}

	void labels_panel::set_labels_for(const entity& entity)
	{
		std::wstring label_text;
		label_text = entity.name() + L"\n";

		auto parameters = entity.get<params>();
		if (parameters)
			label_text += L"Zdrowie: " + std::to_wstring(parameters->health_);

		label_.caption(label_text);
	}
};*/