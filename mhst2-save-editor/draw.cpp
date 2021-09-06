
#include "draw.h"
#include "savedata.h"

#include "Monsters.h"
#include "Genes.h"
#include "TalismanSkills.h"
#include "EquipmentType.h"
#include "FieldAbilities.h"
#include "Items.h"

#include <imgui.h>
#include <Windows.h>
#include <cstdio>

#include <fstream>
#include <string>

void DrawSaveFileWindow();
void DrawEggEditorWindow();
void DrawMonstieEditorWindow();
void DrawPlayerEditorWindow();
void DrawTalismanEditorWindow();
void DrawItemEditorWindow();


void DrawHelpSection();

bool has_input_file = false;
bool show_unknowns = false;
bool i_know_what_im_doing = false;
char input_file[260] = { 0 };
char save_as_file[260] = { 0 };

enum class Tab
{
	SAVE_FILE,
	EGG_EDITOR,
	MONSTIE_EDITOR,
	PLAYER_EDITOR,
	TALISMAN_EDITOR,
	ITEM_EDITOR,


	HELP_SECTION
};

void DrawMainWindow()
{
	using namespace ImGui;
	static Tab selected_tab = Tab::SAVE_FILE;

	BeginTabBar("Editors");

	if (TabItemButton("Save File"))
	{
		selected_tab = Tab::SAVE_FILE;
	}
	if (TabItemButton("Egg Editor"))
	{
		selected_tab = Tab::EGG_EDITOR;
	}
	if (TabItemButton("Monstie Editor"))
	{
		selected_tab = Tab::MONSTIE_EDITOR;
	}
	if (TabItemButton("Player Editor"))
	{
		selected_tab = Tab::PLAYER_EDITOR;
	}
	if (TabItemButton("Talisman Editor"))
	{
		selected_tab = Tab::TALISMAN_EDITOR;
	}
	if (TabItemButton("Item Editor"))
	{
		selected_tab = Tab::ITEM_EDITOR;
	}
	/*if (TabItemButton("Help"))
	{
		selected_tab = Tab::HELP_SECTION;
	}*/

	EndTabBar();

	if (ImGui::BeginPopup("Warning"))
	{
		ImGui::Text("Enable the \"I know what I'm doing\" flag\nin the start menu to edit this.");
	}

	switch (selected_tab)
	{
	case Tab::SAVE_FILE: DrawSaveFileWindow(); break;
	case Tab::EGG_EDITOR: DrawEggEditorWindow(); break;
	case Tab::MONSTIE_EDITOR: DrawMonstieEditorWindow(); break;
	case Tab::PLAYER_EDITOR: DrawPlayerEditorWindow(); break;
	case Tab::TALISMAN_EDITOR: DrawTalismanEditorWindow(); break;
	case Tab::ITEM_EDITOR: DrawItemEditorWindow(); break;
	case Tab::HELP_SECTION: DrawHelpSection(); break;
	default: break;
	}
}

void DrawSaveFileWindow()
{
	ImGui::InputText("Input", input_file, sizeof(input_file), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	
	if (ImGui::Button("Open Save File"))
	{
		OPENFILENAMEA ofn = { 0 };
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFilter = ".sav";
		ofn.lpstrFile = input_file;
		ofn.nMaxFile = sizeof(input_file);

		DWORD attribs = GetFileAttributesA("C:\\Program Files\\Steam\\steamapps\\common\\Monster Hunter Stories 2");
		if (attribs != INVALID_FILE_ATTRIBUTES && attribs & FILE_ATTRIBUTE_DIRECTORY)
		{
			ofn.lpstrInitialDir = "C:\\Program Files\\Steam\\steamapps\\common\\Monster Hunter Stories 2";
		}
		else
		{
			ofn.lpstrInitialDir = NULL;
		}

		ofn.lpstrTitle = "Open Save File";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST;

		if (!GetOpenFileNameA(&ofn))
		{
			printf("GetOpenFileName error (%u)\n", GetLastError());
		}
		else
		{
			sd::ReadFile(input_file);
			strcpy(save_as_file, input_file);
			has_input_file = true;
		}
	}

	if (ImGui::Button("Save", ImVec2(150, 40)))
	{
		if (!has_input_file)
		{
			ImGui::OpenPopup("Error");
		}
		else
		{
			sd::SaveFile(input_file);
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Save As", ImVec2(150, 40)))
	{
		if (!has_input_file)
		{
			ImGui::OpenPopup("Error");
		}
		else
		{
			OPENFILENAMEA ofn = { 0 };
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = ".sav";
			ofn.lpstrFile = save_as_file;
			ofn.nMaxFile = sizeof(save_as_file);

			DWORD attribs = GetFileAttributesA("C:\\Program Files\\Steam\\steamapps\\common\\Monster Hunter Stories 2");
			if (attribs != INVALID_FILE_ATTRIBUTES && attribs & FILE_ATTRIBUTE_DIRECTORY)
			{
				ofn.lpstrInitialDir = "C:\\Program Files\\Steam\\steamapps\\common\\Monster Hunter Stories 2";
			}
			else
			{
				ofn.lpstrInitialDir = NULL;
			}

			ofn.lpstrTitle = "Open Save File";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST;

			if (!GetSaveFileNameA(&ofn))
			{
				printf("GetOpenFileName error (%u)\n", GetLastError());
			}
			else
			{
				sd::SaveFileAs(input_file, save_as_file);
			}
		}
	}

	if (ImGui::BeginPopup("Error"))
	{
		ImGui::Text("Please open a file first.");
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopupModal("Are You Sure?", nullptr, ImGuiWindowFlags_Modal))
	{
		static auto sameline = [] {ImGui::SameLine(); return false; };

		ImGui::Text("This will enable read-only fields that should normally not be changed.\nAre you sure you want to enable this?");
		if (ImGui::Button("Yes") || sameline())
		{
			ImGui::CloseCurrentPopup();
		}
		else if (ImGui::Button("No"))
		{
			i_know_what_im_doing = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::Checkbox("Show Unknowns", &show_unknowns);
	if (ImGui::Checkbox("I know what I'm doing", &i_know_what_im_doing) && i_know_what_im_doing)
	{
		ImGui::OpenPopup("Are You Sure?");
	}

	static bool style_editor = false;

#if defined(DEBUG)
	ImGui::NewLine();
	if (ImGui::Button("Style Editor"))
	{
		style_editor = true;
		ImGui::SetNextWindowFocus();
	}

	if (style_editor)
	{
		ImGui::Begin("Style Editor", &style_editor);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}
#endif

	ImGui::NewLine();

	ImGui::Text("Save Editor for Monster Hunter Stories 2 made by Fexty.");
	ImGui::Text("Save File mapped by DSC-173.");
	ImGui::NewLine();
	ImGui::Text("Use at your own risk. I am not responsible if you mess up your save by using this.");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Always make a backup of your save!");
}

const char* const egg_indices[EGG_MAX_COUNT] = {
	"Egg 1", "Egg 2", "Egg 3", "Egg 4", "Egg 5", "Egg 6",
	"Egg 7", "Egg 8", "Egg 9", "Egg 10", "Egg 11", "Egg 12"
};
const char* const gene_indices[EGG_MAX_COUNT] = {
	"Gene 1", "Gene 2", "Gene 3", "Gene 4", "Gene 5", "Gene 6",
	"Gene 7", "Gene 8", "Gene 9", "Gene 10", "Gene 11", "Gene 12"
};
const char* const gene_editor_indices[EGG_MAX_COUNT] = {
	"Gene Editor 1", "Gene Editor 2", "Gene Editor 3", "Gene Editor 4", "Gene Editor 5", "Gene Editor 6",
	"Gene Editor 7", "Gene Editor 8", "Gene Editor 9", "Gene Editor 10", "Gene Editor 11", "Gene Editor 12"
};
const char* const egg_rarities[3] = {
	"Common",
	"Rare",
	"Super Rare"
};
const char* const den_ranks[3] = {
	"None",
	"Low Rank",
	"High Rank"
};

#define ADVANCED nullptr, nullptr, nullptr, i_know_what_im_doing ? 0 : ImGuiInputTextFlags_ReadOnly
#define MAYBE_GREY_OUT() if (!i_know_what_im_doing) ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(.8f, .8f, .8f, 1.0f));
#define END_GREY_OUT() if (!i_know_what_im_doing) ImGui::PopStyleColor();

void DrawEggEditorWindow()
{
	ImGui::BeginGroup();

	static int selected_egg = 0;

	if (ImGui::BeginCombo("Eggs", egg_indices[selected_egg]))
	{

		for (int i = 0; i < EGG_MAX_COUNT; i++)
		{
			if (ImGui::Selectable(egg_indices[i], i == selected_egg))
			{
				selected_egg = i;
			}
		}

		ImGui::EndCombo();
	}
	
	ImGui::EndGroup();
	ImGui::BeginGroup();

	sd::Egg& egg = sd::eggs[selected_egg];

	if (ImGui::BeginCombo("Monster ID", MonsterNames[egg.monster_id]))
	{
		for (int i = 0; i < MonsterNames.size(); i++)
		{
			if (ImGui::Selectable(MonsterNames[i], i == egg.monster_id))
			{
				egg.monster_id = i;
			}
		}

		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo("Rarity", egg_rarities[egg.rarity]))
	{
		for (int i = 0; i < 3; i++)
		{
			if (ImGui::Selectable(egg_rarities[i], i == egg.rarity))
			{
				egg.rarity = i;
			}
		}

		ImGui::EndCombo();
	}
	ImGui::Checkbox("Exists", &egg.exists);

	for (int i = 0; i < GENES_MAX_COUNT; i++)
	{
		sd::Gene& gene = egg.genes[i];

		ImGui::PushStyleColor(ImGuiCol_Button, gene_colors[gene.gene_id]);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, gene_colors[gene.gene_id]);

		if (ImGui::Button(gene_indices[i], ImVec2(90, 90)))
		{
			ImGui::OpenPopup(gene_editor_indices[i]);
		}

		if (ImGui::BeginPopup(gene_editor_indices[i]))
		{
			if (ImGui::BeginCombo("Gene", GeneNames[gene.gene_id]))
			{
				for (int i = 0; i < GeneNames.size(); i++)
				{
					if (ImGui::Selectable(GeneNames[i], i == gene.gene_id))
					{
						gene.gene_id = i;
					}
				}

				ImGui::EndCombo();
			}

			ImGui::Checkbox("Locked", &gene.level_locked);
			ImGui::InputScalar("Gene Level", ImGuiDataType_U8, &gene.gene_level);

			ImGui::EndPopup();
		}

		ImGui::PopStyleColor(2);

		if ((i + 1) % 3) ImGui::SameLine();
	}

	if (ImGui::BeginCombo("Den Rank", den_ranks[egg.den_rank]))
	{
		for (u32 i = 0; i < 3; i++)
		{
			if (ImGui::Selectable(den_ranks[i], i == egg.den_rank))
			{
				egg.den_rank = i;
			}
		}

		ImGui::EndCombo();
	}

	MAYBE_GREY_OUT();
	ImGui::InputScalar("Den Rarity", ImGuiDataType_U8, &egg.den_rarity, ADVANCED);
	ImGui::InputScalar("Den Area", ImGuiDataType_U32, &egg.den_area, ADVANCED);
	END_GREY_OUT();

	if (show_unknowns)
	{
		ImGui::InputScalarN("Unk0", ImGuiDataType_S32, egg.unk, 5);
		ImGui::InputScalarN("Unk2", ImGuiDataType_S32, egg.unk2, 3);
	}

	ImGui::EndGroup();
}

void DrawMonstieEditorWindow()
{
	ImGui::BeginGroup();

	static int selected_monstie = 0;

	if (ImGui::BeginCombo("Monsties", sd::monsties[selected_monstie].name))
	{
		for (int i = 0; i < MONSTIE_MAX_COUNT; i++)
		{
			std::string name = std::to_string(i + 1) + "\t" + sd::monsties[i].name;
			if (ImGui::Selectable(name.c_str(), i == selected_monstie))
			{
				selected_monstie = i;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::EndGroup();
	ImGui::BeginGroup();

	using DT = ImGuiDataType_;
	
	sd::Monstie& m = sd::monsties[selected_monstie];

	ImGui::InputText("Name", m.name, sizeof(m.name));
	ImGui::InputScalar("Sorting ID", DT::ImGuiDataType_U32, &m.sorting_id);
	
	if (ImGui::BeginCombo("Monster ID", MonsterNames[m.monster_id]))
	{
		for (int i = 0; i < MonsterNames.size(); i++)
		{
			if (ImGui::Selectable(MonsterNames[i], i == m.monster_id))
			{
				m.monster_id = i;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::InputScalar("Size", DT::ImGuiDataType_U8, &m.size);
	ImGui::Checkbox("Favorite", &m.favorite);

	ImGui::NewLine();

	MAYBE_GREY_OUT();
	ImGui::InputScalar("Kinship Skill ID", DT::ImGuiDataType_U16, &m.kskill_id, ADVANCED);
	ImGui::InputScalar("Starting Kinship", DT::ImGuiDataType_U32, &m.ks_start, ADVANCED);
	ImGui::InputScalar("Unknown Kinship", DT::ImGuiDataType_S64, &m.ks_start2, ADVANCED);
	END_GREY_OUT();

	if (ImGui::BeginCombo("Field Ability 1", FieldAbilities[m.ability1]))
	{
		for (int i = 0; i < FieldAbilities.size(); i++)
		{
			if (ImGui::Selectable(FieldAbilities[i], i == m.ability1))
			{
				m.ability1 = i;
			}
		}

		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo("Field Ability 2", FieldAbilities[m.ability2]))
	{
		for (int i = 0; i < FieldAbilities.size(); i++)
		{
			if (ImGui::Selectable(FieldAbilities[i], i == m.ability2))
			{
				m.ability2 = i;
			}
		}

		ImGui::EndCombo();
	}
	ImGui::NewLine();

	ImGui::Checkbox("Locked", &m.locked);

	ImGui::InputScalar("Current HP", DT::ImGuiDataType_U32, &m.cur_hp);
	MAYBE_GREY_OUT();
	ImGui::InputScalar("Max HP", DT::ImGuiDataType_U32, &m.max_hp, ADVANCED);
	END_GREY_OUT();

	ImGui::InputScalar("Level", DT::ImGuiDataType_U16, &m.level);
	ImGui::InputScalar("Exp", DT::ImGuiDataType_U32, &m.exp);
	ImGui::NewLine();

	MAYBE_GREY_OUT();
	ImGui::Text("Attack");
	ImGui::InputScalar("Normal Attack", DT::ImGuiDataType_U16, &m.normal_atk, ADVANCED);
	ImGui::InputScalar("Fire Attack", DT::ImGuiDataType_U16, &m.fire_atk, ADVANCED);
	ImGui::InputScalar("Water Attack", DT::ImGuiDataType_U16, &m.water_atk, ADVANCED);
	ImGui::InputScalar("Thunder Attack", DT::ImGuiDataType_U16, &m.thunder_atk, ADVANCED);
	ImGui::InputScalar("Ice Attack", DT::ImGuiDataType_U16, &m.ice_atk, ADVANCED);
	ImGui::InputScalar("Dragon Attack", DT::ImGuiDataType_U16, &m.dragon_atk, ADVANCED);
	ImGui::NewLine();

	ImGui::Text("Defense");
	ImGui::InputScalar("Normal Defense", DT::ImGuiDataType_U16, &m.normal_def, ADVANCED);
	ImGui::InputScalar("Fire Defense", DT::ImGuiDataType_U16, &m.fire_def, ADVANCED);
	ImGui::InputScalar("Water Defense", DT::ImGuiDataType_U16, &m.water_def, ADVANCED);
	ImGui::InputScalar("Thunder Defense", DT::ImGuiDataType_U16, &m.thunder_def, ADVANCED);
	ImGui::InputScalar("Ice Defense", DT::ImGuiDataType_U16, &m.ice_def, ADVANCED);
	ImGui::InputScalar("Dragon Defense", DT::ImGuiDataType_U16, &m.dragon_def, ADVANCED);
	ImGui::NewLine();
	END_GREY_OUT();

	ImGui::InputScalar("Vitality Nutriments", DT::ImGuiDataType_U8, &m.vit_nutriments);
	ImGui::InputScalar("Attack Nutriments", DT::ImGuiDataType_U8, &m.atk_nutriments);
	ImGui::InputScalar("Defense Nutriments", DT::ImGuiDataType_U8, &m.def_nutriments);

	ImGui::InputScalar("HP Bonus", DT::ImGuiDataType_U8, &m.hp_bonus);
	ImGui::NewLine();

	ImGui::Text("Attack Bonus");
	ImGui::InputScalar("Normal Attack Bonus", DT::ImGuiDataType_S8, &m.normal_atk_bonus);
	ImGui::InputScalar("Fire Attack Bonus", DT::ImGuiDataType_S8, &m.fire_atk_bonus);
	ImGui::InputScalar("Water Attack Bonus", DT::ImGuiDataType_S8, &m.water_atk_bonus);
	ImGui::InputScalar("Thunder Attack Bonus", DT::ImGuiDataType_S8, &m.thunder_atk_bonus);
	ImGui::InputScalar("Ice Attack Bonus", DT::ImGuiDataType_S8, &m.ice_atk_bonus);
	ImGui::InputScalar("Dragon Attack Bonus", DT::ImGuiDataType_S8, &m.dragon_atk_bonus);
	ImGui::NewLine();

	ImGui::Text("Defense Bonus");
	ImGui::InputScalar("Normal Defense Bonus", DT::ImGuiDataType_S8, &m.normal_def_bonus);
	ImGui::InputScalar("Fire Defense Bonus", DT::ImGuiDataType_S8, &m.fire_def_bonus);
	ImGui::InputScalar("Water Defense Bonus", DT::ImGuiDataType_S8, &m.water_def_bonus);
	ImGui::InputScalar("Thunder Defense Bonus", DT::ImGuiDataType_S8, &m.thunder_def_bonus);
	ImGui::InputScalar("Ice Defense Bonus", DT::ImGuiDataType_S8, &m.ice_def_bonus);
	ImGui::InputScalar("Dragon Defense Bonus", DT::ImGuiDataType_S8, &m.dragon_def_bonus);
	ImGui::NewLine();

	if (show_unknowns)
	{
		ImGui::InputScalar ("Emp  ", DT::ImGuiDataType_U8, &m.emp);
		ImGui::InputScalar ("Unk01", DT::ImGuiDataType_U8, &m.unk1);
		ImGui::InputScalar ("Unk02", DT::ImGuiDataType_U8, &m.unk2);
		ImGui::InputScalarN("Unk03", DT::ImGuiDataType_S32, m.unk3, 2);
		ImGui::InputScalar ("Unk04", DT::ImGuiDataType_S16, &m.unk4);
		ImGui::InputScalarN("Unk05", DT::ImGuiDataType_S32, m.unk5, 10);
		ImGui::InputScalarN("Unk06", DT::ImGuiDataType_S32, m.unk6, 2);
		ImGui::InputScalar ("Unk07", DT::ImGuiDataType_U8, &m.unk7);
		ImGui::InputScalarN("Unk08", DT::ImGuiDataType_U8, m.unk8, 3);
		ImGui::InputScalar ("Unk09", DT::ImGuiDataType_S32, &m.unk9);
		ImGui::InputScalarN("Unk10", DT::ImGuiDataType_S32, m.unk10, 35);
		ImGui::InputScalarN("Unk11", DT::ImGuiDataType_S32, m.unk11, 2);
		ImGui::InputFloat  ("Unk12", &m.unk12);
		ImGui::InputScalar ("Unk13", DT::ImGuiDataType_S16, &m.unk13);
		ImGui::InputScalarN("Unk14", DT::ImGuiDataType_S32, m.unk14, 2);
		ImGui::InputScalar ("Unk15", DT::ImGuiDataType_S32, &m.unk15);
		ImGui::InputScalar ("Unk16", DT::ImGuiDataType_S32, &m.unk16);
	}

	for (int i = 0; i < GENES_MAX_COUNT; i++)
	{
		sd::Gene& gene = m.genes[i];

		ImGui::PushStyleColor(ImGuiCol_Button, gene_colors[gene.gene_id]);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, gene_colors[gene.gene_id]);

		if (ImGui::Button(gene_indices[i], ImVec2(90, 90)))
		{
			ImGui::OpenPopup(gene_editor_indices[i]);
		}

		if (ImGui::BeginPopup(gene_editor_indices[i], ImGuiWindowFlags_MenuBar))
		{
			if (ImGui::BeginCombo("Gene", GeneNames[gene.gene_id]))
			{
				for (int i = 0; i < GeneNames.size(); i++)
				{
					if (ImGui::Selectable(GeneNames[i], i == gene.gene_id))
					{
						gene.gene_id = i;
					}
				}

				ImGui::EndCombo();
			}

			ImGui::Checkbox("Locked", &gene.level_locked);
			ImGui::InputScalar("Gene Level", ImGuiDataType_U8, &gene.gene_level);

			ImGui::EndPopup();
		}

		ImGui::PopStyleColor(2);

		if ((i + 1) % 3) ImGui::SameLine();
	}

	ImGui::EndGroup();
}

void DrawPlayerEditorWindow()
{
	ImGui::BeginGroup();

	int selected_player = 0;

	MAYBE_GREY_OUT();
	if (i_know_what_im_doing && ImGui::BeginCombo("Player", sd::players[selected_player].name))
	{
		for (int i = 0; i < PLAYER_MAX_COUNT; i++)
		{
			if (sd::players[i].name[0] == '\0') break;

			if (ImGui::Selectable(sd::players[i].name, i == selected_player))
			{
				selected_player = i;
			}
		}

		ImGui::EndCombo();
	}
	END_GREY_OUT();

	sd::Player& p = sd::players[selected_player];

	ImGui::InputText("Name", p.name, sizeof(p.name));
	ImGui::InputScalar("Level", ImGuiDataType_U16, &p.level);
	ImGui::InputScalar("Exp", ImGuiDataType_U32, &p.exp);
	ImGui::InputScalar("Zenny", ImGuiDataType_U32, &sd::zenny);

	ImGui::EndGroup();
}

void DrawTalismanEditorWindow()
{
	ImGui::BeginGroup();

	static int selected_index = 0;
	if (ImGui::BeginCombo("Talisman Box", std::to_string(selected_index).c_str()))
	{
		for (int i = 0; i < TALISMAN_MAX_COUNT; i++)
		{
			sd::Talisman& t = sd::talismans[i];
			std::string label = std::to_string(i) + " " + GetSkillName(t.skill1) + ", " + GetSkillName(t.skill2);
			if (ImGui::Selectable(label.c_str(), i == selected_index))
			{
				selected_index = i;
			}
		}

		ImGui::EndCombo();
	}

	sd::Talisman& t = sd::talismans[selected_index];

	MAYBE_GREY_OUT();
	if (i_know_what_im_doing && ImGui::BeginCombo("Equipment Type", EqType.at(t.equipment_type)))
	{
		for (const auto& [id, name] : EqType)
		{
			if (ImGui::Selectable(name, id == t.equipment_type))
			{
				t.equipment_type = id;
			}
		}

		ImGui::EndCombo();
	}
	END_GREY_OUT();

	ImGui::InputScalar("Base ID", ImGuiDataType_U16, &t.type);
	ImGui::InputScalar("Level", ImGuiDataType_U16, &t.level);

	if (show_unknowns)
	{
		ImGui::InputScalar("Unk0", ImGuiDataType_U16, &t.unk0);
		ImGui::InputScalarN("Unk1", ImGuiDataType_S32, t.unk1, 2);
		ImGui::InputScalar("Unk2", ImGuiDataType_U8, &t.unk2);
		ImGui::InputScalarN("Unk3", ImGuiDataType_S32, t.unk3, 5);
		ImGui::InputScalar("Unk4", ImGuiDataType_S32, &t.unk4);
	}

	ImGui::Text("Equipped");
	if (ImGui::RadioButton("Not Equipped", t._equipped == 0x0))		t._equipped = 0x00; // 0
	if (ImGui::RadioButton("Primary Weapon", t._equipped == 0x1))	t._equipped = 0x01; // 1 << 0
	if (ImGui::RadioButton("Secondary Weapon", t._equipped == 0x2)) t._equipped = 0x02;	// 1 << 1
	if (ImGui::RadioButton("Tertiary Weapon", t._equipped == 0x4))	t._equipped = 0x04;	// 1 << 2
	if (ImGui::RadioButton("Armor Slot", t._equipped == 0x8))		t._equipped = 0x08;	// 1 << 3
	if (ImGui::RadioButton("Talisman Slot", t._equipped == 0x10))	t._equipped = 0x10;	// 1 << 4

	ImGui::Checkbox("Exists", (bool*)&t.exists);
	ImGui::InputScalar("Rarity", ImGuiDataType_U32, &t.rarity);

	if (ImGui::BeginCombo("Skill 1", GetSkillName(t.skill1)))
	{
		if (ImGui::Selectable("Empty", t.skill1 == 0))
		{
			t.skill1 = 0;
		}

		for (int i = 0; i < SkillNames.size(); i++)
		{
			u16 skl_id = i + 3000;

			if (ImGui::Selectable(SkillNames[i], skl_id == t.skill1))
			{
				t.skill1 = skl_id;
			}
		}

		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo("Skill 2", GetSkillName(t.skill2)))
	{
		if (ImGui::Selectable("Empty", t.skill2 == 0))
		{
			t.skill2 = 0;
		}

		for (int i = 0; i < SkillNames.size(); i++)
		{
			u16 skl_id = i + 3000;

			if (ImGui::Selectable(SkillNames[i], skl_id == t.skill2))
			{
				t.skill2 = skl_id;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::EndGroup();
}
#include "filtered_combobox.h"
void DrawItemEditorWindow()
{
	ImGui::BeginChild("##ItemEditorWindow");

	std::string amt_id = "Amount##";
	std::string unk_id = "Unk##";

	for (int i = 0; i < ITEM_MAX_COUNT; i++)
	{
		auto& item = sd::items[i];
		std::string id = std::to_string(i);

		int idx = static_cast<int>(item.id);
		ImGui::ComboWithFilter(id.c_str(), &idx, ItemNames.data(), ItemNames.size());
		item.id = static_cast<u16>(idx);

		ImGui::PushItemWidth(300.0f);
		ImGui::SameLine();
		ImGui::InputScalar((amt_id + id).c_str(), ImGuiDataType_U16, &item.amount);

		if (show_unknowns)
		{
			ImGui::SameLine();
			ImGui::InputInt((unk_id + id).c_str(), &item.unk);
		}
		ImGui::PopItemWidth();
	}

	ImGui::EndChild();
}

#define VA_ARGS(...) , ##__VA_ARGS__
#define Title(text, ...)\
ImGui::PushFont(&heading);\
ImGui::Text(text VA_ARGS(__VA_ARGS__));\
ImGui::PopFont();

void DrawHelpSection()
{
	static bool init = false;
	static ImFont heading;

	if (!init)
	{
		heading = *ImGui::GetFont();
		//heading.FontSize *= 1.1f;
		heading.Scale *= 1.1f;
		init = true;
	}

	Title("1 Extracting your save");

	ImGui::Text("Test");
}
