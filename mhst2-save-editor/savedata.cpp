
#include "savedata.h"

#include <cstdio>
#include <filesystem>



sd::Egg* sd::eggs = nullptr;
sd::Monstie* sd::monsties = nullptr;
sd::Player* sd::players = nullptr;
sd::Talisman* sd::talismans = nullptr;
sd::Item* sd::items = nullptr;
u8* sd::itemflags = nullptr;
u32 sd::zenny = 0;

#define EGG_OFFSET		0x10CDC		// Implemented
#define PLAYER_OFFSET	0x2D2AC8	// Implemented
#define MONSTIE_OFFSET	0x2D72F8	// Implemented
#define TALISMAN_OFFSET	0xD9AC		// Implemented
#define WEAPON_OFFSET	0x3EFC		// 
#define ARMOR_OFFSET	0xA16C		// 
#define ZENNY_OFFSET	0x78		// Implemented
#define ITEM_OFFSET		0x84		// Implemented
#define ITMS_OFFSET		0x12B98		// Implemented

size_t GetFileSize(FILE* f)
{
	std::fseek(f, 0, SEEK_END);
	size_t s = std::ftell(f);
	std::fseek(f, 0, SEEK_SET);

	return s;
}

void sd::ReadFile(const char* filepath)
{
	FILE* file = std::fopen(filepath, "rb");

	if (GetFileSize(file) < 0x8080B0)
	{
		printf("Invalid file size\n");
		return;
	}

	std::fseek(file, ITEM_OFFSET, SEEK_SET);
	std::fread(items, sizeof(Item), ITEM_MAX_COUNT, file);

	std::fseek(file, ITMS_OFFSET, SEEK_SET);
	std::fread(itemflags, sizeof(u8), ITEMFLAG_MAX_COUNT, file);

	std::fseek(file, EGG_OFFSET, SEEK_SET);
	std::fread(eggs, sizeof(Egg), EGG_MAX_COUNT, file);

	std::fseek(file, MONSTIE_OFFSET, SEEK_SET);
	std::fread(monsties, sizeof(Monstie), MONSTIE_MAX_COUNT, file);

	std::fseek(file, PLAYER_OFFSET, SEEK_SET);
	std::fread(players, sizeof(Player), PLAYER_MAX_COUNT, file);

	std::fseek(file, TALISMAN_OFFSET, SEEK_SET);
	std::fread(talismans, sizeof(Talisman), TALISMAN_MAX_COUNT, file);

	std::fseek(file, ZENNY_OFFSET, SEEK_SET);
	std::fread(&zenny, sizeof(u32), 1, file);

	std::fclose(file);
}

void sd::SaveFile(const char* filepath)
{
	FILE* file = std::fopen(filepath, "rb+");

	if (GetFileSize(file) < 0x8080B0)
	{
		printf("Invalid file size\n");
		return;
	}

	AdjustItemflags();

	std::fseek(file, ITEM_OFFSET, SEEK_SET);
	std::fwrite(items, sizeof(Item), ITEM_MAX_COUNT, file);

	std::fseek(file, ITMS_OFFSET, SEEK_SET);
	std::fwrite(itemflags, sizeof(u8), ITEMFLAG_MAX_COUNT, file);

	std::fseek(file, EGG_OFFSET, SEEK_SET);
	std::fwrite(eggs, sizeof(Egg), EGG_MAX_COUNT, file);

	std::fseek(file, MONSTIE_OFFSET, SEEK_SET);
	std::fwrite(monsties, sizeof(Monstie), MONSTIE_MAX_COUNT, file);

	std::fseek(file, PLAYER_OFFSET, SEEK_SET);
	std::fwrite(players, sizeof(Player), PLAYER_MAX_COUNT, file);

	std::fseek(file, TALISMAN_OFFSET, SEEK_SET);
	std::fwrite(talismans, sizeof(Talisman), TALISMAN_MAX_COUNT, file);

	std::fseek(file, ZENNY_OFFSET, SEEK_SET);
	std::fwrite(&zenny, sizeof(u32), 1, file);

	std::fclose(file);
}

void sd::SaveFileAs(const char* original, const char* new_path)
{
	std::filesystem::copy_file(original, new_path);
	sd::SaveFile(new_path);
}

void sd::AdjustItemflags()
{
	for (int i = 0; i < ITEM_MAX_COUNT; i++)
	{
		Item& itm = items[i];
		if (itm.id != 0 && itm.amount != 0)
		{
			itemflags[itm.id / 8] |= (1UI8 << (itm.id % 8));
		}
	}
}
