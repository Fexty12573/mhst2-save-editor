#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <string>

namespace ImGui
{
	void FilteredComboBox(
		const char* label,
		const char* private_id,
		char* buffer,
		size_t buflen,
		const char* const* items,
		size_t count,
		int* selected_idx
	);
	bool ComboWithFilter(const char* label, int* current_item, const char* const* items, size_t items_count, bool disabled = false);
}
