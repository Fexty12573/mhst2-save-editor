#pragma once

#include <array>

extern const std::array<const char*, 316> skill_names;
static const char* empty = "Empty";

inline const char* GetSkillName(unsigned short id)
{
	if (id >= 3000) return skill_names[id - 3000];
	else return empty;
}
