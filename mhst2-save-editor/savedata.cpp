
#include "savedata.h"
#include "Items.h"

#include <cstdio>
#include <filesystem>

std::vector<sd::Egg>		sd::eggs(EGG_MAX_COUNT, { 0 });
std::vector<sd::Monstie>	sd::monsties(MONSTIE_MAX_COUNT, { 0 });
std::vector<sd::Player>		sd::players(PLAYER_MAX_COUNT, { 0 });
std::vector<sd::Talisman>	sd::talismans(TALISMAN_MAX_COUNT, { 0 });
std::vector<sd::Item>		sd::items(ITEM_MAX_COUNT, { 0 });
std::vector<u8>				sd::itemflags(ITEMFLAG_MAX_COUNT, 0);
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

	for (size_t i = 0; i < items.size(); ++i)
	{
		std::fread(&items[i].item, sizeof(Item::item), 1, file);
		items[i].slot = i;
	}

	std::fseek(file, ITMS_OFFSET, SEEK_SET);
	std::fread(itemflags.data(), sizeof(u8), ITEMFLAG_MAX_COUNT, file);

	std::fseek(file, EGG_OFFSET, SEEK_SET);
	std::fread(eggs.data(), sizeof(Egg), EGG_MAX_COUNT, file);

	std::fseek(file, MONSTIE_OFFSET, SEEK_SET);
	std::fread(monsties.data(), sizeof(Monstie), MONSTIE_MAX_COUNT, file);

	std::fseek(file, PLAYER_OFFSET, SEEK_SET);
	std::fread(players.data(), sizeof(Player), PLAYER_MAX_COUNT, file);

	std::fseek(file, TALISMAN_OFFSET, SEEK_SET);
	std::fread(talismans.data(), sizeof(Talisman), TALISMAN_MAX_COUNT, file);

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

	SortItemsBySlot();
	AdjustItemflags();

	std::fseek(file, ITEM_OFFSET, SEEK_SET);
	for (const auto& i : items)
		std::fwrite(&i.item, sizeof(Item::item), 1, file);

	std::fseek(file, ITMS_OFFSET, SEEK_SET);
	std::fwrite(itemflags.data(), sizeof(u8), ITEMFLAG_MAX_COUNT, file);

	std::fseek(file, EGG_OFFSET, SEEK_SET);
	std::fwrite(eggs.data(), sizeof(Egg), EGG_MAX_COUNT, file);

	std::fseek(file, MONSTIE_OFFSET, SEEK_SET);
	std::fwrite(monsties.data(), sizeof(Monstie), MONSTIE_MAX_COUNT, file);

	std::fseek(file, PLAYER_OFFSET, SEEK_SET);
	std::fwrite(players.data(), sizeof(Player), PLAYER_MAX_COUNT, file);

	std::fseek(file, TALISMAN_OFFSET, SEEK_SET);
	std::fwrite(talismans.data(), sizeof(Talisman), TALISMAN_MAX_COUNT, file);

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
		auto& itm = items[i].item;
		if (itm.id != 0 && itm.amount != 0)
		{
			itemflags[itm.id / 8] |= (1UI8 << (itm.id % 8));
		}
	}
}

void sd::SortItemsBySlot(bool descending)
{
	std::sort(items.begin(), items.end(), [&](Item& a, Item& b)
	{
		return (descending ? (a.slot > b.slot) : (a.slot < b.slot));
	});
}

void sd::SortItemsByID(bool descending)
{
	std::sort(items.begin(), items.end(), [&](Item& a, Item& b)
	{
		return (descending ? (a.item.id > b.item.id) : (a.item.id < b.item.id));
	});
}

void sd::SortItemsByName(bool descending)
{
	std::sort(items.begin(), items.end(), [&](Item& a, Item& b)
	{
		std::string astr = ItemNames[a.item.id];
		std::string bstr = ItemNames[b.item.id];

		return (descending ? (astr > bstr) : (astr < bstr));
	});
}

void sd::SortItemsByAmount(bool descending)
{
	std::sort(items.begin(), items.end(), [&](Item& a, Item& b)
	{
		return (descending ? (a.item.amount > b.item.amount) : (a.item.amount < b.item.amount));
	});
}
