#pragma once

using u8 = unsigned char;
using s8 = signed char;
using u16 = unsigned short;
using s16 = signed short;
using u32 = unsigned int;
using s32 = signed int;
using u64 = unsigned long long;
using s64 = signed long long;

#define GENES_MAX_COUNT 9
#define EGG_MAX_COUNT 12
#define MONSTIE_MAX_COUNT 500
#define WEAPON_MAX_COUNT 700
#define ARMOR_MAX_COUNT 400
#define TALISMAN_MAX_COUNT 200
#define PLAYER_MAX_COUNT 31

namespace sd
{
#pragma pack(push, 1)
	struct Gene
	{
		u16 gene_id;
		bool level_locked;
		u8 gene_level;
	};
	struct Egg
	{
		u32 monster_id;
		u32 rarity;
		Gene genes[GENES_MAX_COUNT];
		s32 unk[5];
		u32 den_rank;
		u8 den_rarity;
		u8 unk1;
		s16 empty;
		u32 den_area;
		u32 unk2[3];
		s32 empty2[8];
	};
	struct Monstie
	{
		char name[48];
		u32 sorting_id;
		u32 monster_id;
		s32 unk;

		u8 ability1;
		u8 ability2;

		u8 unk2[2];
		s32 unk3[5];
		s16 unk4;

		u16 level;

		s32 unk5[11];

		u16 normal_atk;
		u16 fire_atk;
		u16 water_atk;
		u16 thunder_atk;
		u16 ice_atk;
		u16 dragon_atk;

		s32 unk6[2];

		u16 normal_def;
		u16 fire_def;
		u16 water_def;
		u16 thunder_def;
		u16 ice_def;
		u16 dragon_def;

		s32 unk7;

		u8 hp_bonus;

		u8 normal_atk_bonus;
		u8 fire_atk_bonus;
		u8 water_atk_bonus;
		u8 thunder_atk_bonus;
		u8 ice_atk_bonus;
		u8 dragon_atk_bonus;

		u8 normal_def_bonus;
		u8 fire_def_bonus;
		u8 water_def_bonus;
		u8 thunder_def_bonus;
		u8 ice_def_bonus;
		u8 dragon_def_bonus;

		u8 unk8[3];
		s32 unk9;

		u32 exp;

		s32 unk10[35];

		Gene genes[GENES_MAX_COUNT];

		s32 unk11[11];
	};
	struct Player
	{
		char name[18];
		u8 unk1[216];
		u16 level;
		u8 unk2[100];
		u32 exp;
	};
#pragma pack(pop)

	extern Egg eggs[EGG_MAX_COUNT];
	extern Monstie monsties[MONSTIE_MAX_COUNT];
	extern Player players[PLAYER_MAX_COUNT];
	extern u32 zenny;
	
	void ReadFile(const char* filepath);
	void SaveFile(const char* filepath);
	void SaveFileAs(const char* original, const char* new_path);
}
