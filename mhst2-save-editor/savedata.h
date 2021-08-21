#pragma once

#include <string.h>

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
#define ITEM_MAX_COUNT 1999
#define ITEMFLAG_MAX_COUNT 1780
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
		bool exists;
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

		u8 emp;
		u8 size;
		bool favorite;
		u8 unk1;

		u8 ability1;
		u8 ability2;

		u8 unk2;
		bool locked;

		s32 unk3[2];

		u32 cur_hp;
		u32 max_hp;
		u32 speed;

		s16 unk4;

		u16 level;

		float unk12;
		s32 unk5[10];

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

		u8 vit_nutriments;
		u8 atk_nutriments;
		u8 def_nutriments;
		u8 unk7;

		u8 hp_bonus;

		s8 normal_atk_bonus;
		s8 fire_atk_bonus;
		s8 water_atk_bonus;
		s8 thunder_atk_bonus;
		s8 ice_atk_bonus;
		s8 dragon_atk_bonus;

		s8 normal_def_bonus;
		s8 fire_def_bonus;
		s8 water_def_bonus;
		s8 thunder_def_bonus;
		s8 ice_def_bonus;
		s8 dragon_def_bonus;

		u8 unk8[3];
		s32 unk9;

		u32 exp;

		s32 unk10[35];

		Gene genes[GENES_MAX_COUNT];

		s32 unk11[2];

		u16 kskill_id;
		s16 unk13;
		s32 unk14[3];
		u32 ks_start;
		s32 unk15;
		u64 ks_start2;
		s32 unk16;
	};
	struct Player
	{
		char name[18];
		u8 unk1[216];
		u16 level;
		u8 unk2[100];
		u32 exp;
	};
	struct Talisman
	{
		u16 equipment_type;
		u16 type;
		u16 level;
		u16 unk0;
		s32 unk1[2];
		u8 unk2;
		union {
			struct {
				bool primary_weapon : 1;
				bool secondary_weapon : 1;
				bool tertiary_weapon : 1;
				bool armor_slot : 1;
				bool talisman_slot : 1;
				bool : 3;
			} equipped;
			u8 _equipped; // Full byte
		};
		u16 exists;
		s32 unk3[4];
		u32 rarity;
		u16 skill1;
		u16 skill2;
		s32 unk4;
	};
	struct Item
	{
		u16 id;
		u16 amount;
		s32 unk;
	};
#pragma pack(pop)

	extern Egg* eggs;
	extern Monstie* monsties;
	extern Player* players;
	extern Talisman* talismans;
	extern Item* items;
	extern u8* itemflags;
	extern u32 zenny;

	inline void AllocateArrays()
	{
		eggs = new Egg[EGG_MAX_COUNT];
		monsties = new Monstie[MONSTIE_MAX_COUNT];
		players = new Player[PLAYER_MAX_COUNT];
		talismans = new Talisman[TALISMAN_MAX_COUNT];
		items = new Item[ITEM_MAX_COUNT];
		itemflags = new u8[ITEMFLAG_MAX_COUNT];

		memset(eggs, 0, sizeof(Egg) * EGG_MAX_COUNT);
		memset(monsties, 0, sizeof(Monstie) * MONSTIE_MAX_COUNT);
		memset(players, 0, sizeof(Player) * PLAYER_MAX_COUNT);
		memset(talismans, 0, sizeof(Talisman) * TALISMAN_MAX_COUNT);
		memset(items, 0, sizeof(Item) * ITEM_MAX_COUNT);
		memset(itemflags, 0, sizeof(u8) * ITEMFLAG_MAX_COUNT);
	}

	inline void DeleteArrays()
	{
		delete[] eggs;
		delete[] monsties;
		delete[] players;
		delete[] talismans;
	}
	
	void ReadFile(const char* filepath);
	void SaveFile(const char* filepath);
	void SaveFileAs(const char* original, const char* new_path);

	void AdjustItemflags();
}
