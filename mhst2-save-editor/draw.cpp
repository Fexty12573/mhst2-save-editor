
#include "draw.h"
#include "savedata.h"

#include "Monsters.h"
#include "Genes.h"
#include "TalismanSkills.h"
#include "EquipmentType.h"

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

bool has_input_file = false;
bool show_unknowns = false;
char input_file[260] = { 0 };
char save_as_file[260] = { 0 };

enum class Tab
{
	SAVE_FILE,
	EGG_EDITOR,
	MONSTIE_EDITOR,
	PLAYER_EDITOR,
	TALISMAN_EDITOR
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

	EndTabBar();

	switch (selected_tab)
	{
	case Tab::SAVE_FILE: DrawSaveFileWindow(); break;
	case Tab::EGG_EDITOR: DrawEggEditorWindow(); break;
	case Tab::MONSTIE_EDITOR: DrawMonstieEditorWindow(); break;
	case Tab::PLAYER_EDITOR: DrawPlayerEditorWindow(); break;
	case Tab::TALISMAN_EDITOR: DrawTalismanEditorWindow(); break;
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

	ImGui::Checkbox("Show Unknowns", &show_unknowns);

	static bool style_editor = false;

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

	if (ImGui::BeginCombo("Monster ID", monster_names[egg.monster_id]))
	{
		for (int i = 0; i < monster_names.size(); i++)
		{
			if (ImGui::Selectable(monster_names[i], i == egg.monster_id))
			{
				egg.monster_id = i;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::InputScalar("Rarity", ImGuiDataType_U32, &egg.rarity);

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
			if (ImGui::BeginCombo("Gene", gene_names[gene.gene_id]))
			{
				for (int i = 0; i < gene_names.size(); i++)
				{
					if (ImGui::Selectable(gene_names[i], i == gene.gene_id))
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

	ImGui::InputScalar("Den Rank", ImGuiDataType_U16, &egg.den_rank);
	ImGui::InputScalar("Den Rarity", ImGuiDataType_U16, &egg.den_rarity);
	ImGui::InputScalar("Den Area", ImGuiDataType_U16, &egg.den_area);

	if (show_unknowns)
	{
		ImGui::InputScalarN("Unk0", ImGuiDataType_S32, &egg.unk, 5);
		ImGui::InputScalar("Unk1", ImGuiDataType_U16, &egg.unk1);
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
	
	if (ImGui::BeginCombo("Monster ID", monster_names[m.monster_id]))
	{
		for (int i = 0; i < monster_names.size(); i++)
		{
			if (ImGui::Selectable(monster_names[i], i == m.monster_id))
			{
				m.monster_id = i;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::NewLine();

	ImGui::InputScalar("Ability 1", DT::ImGuiDataType_U8, &m.ability1);
	ImGui::InputScalar("Ability 2", DT::ImGuiDataType_U8, &m.ability2);
	ImGui::NewLine();

	ImGui::InputScalar("Level", DT::ImGuiDataType_U16, &m.level);
	ImGui::InputScalar("Exp", DT::ImGuiDataType_U32, &m.exp);
	ImGui::NewLine();

	ImGui::Text("Attack");
	ImGui::InputScalar("Normal Attack", DT::ImGuiDataType_U16, &m.normal_atk);
	ImGui::InputScalar("Fire Attack", DT::ImGuiDataType_U16, &m.fire_atk);
	ImGui::InputScalar("Water Attack", DT::ImGuiDataType_U16, &m.water_atk);
	ImGui::InputScalar("Thunder Attack", DT::ImGuiDataType_U16, &m.thunder_atk);
	ImGui::InputScalar("Ice Attack", DT::ImGuiDataType_U16, &m.ice_atk);
	ImGui::InputScalar("Dragon Attack", DT::ImGuiDataType_U16, &m.dragon_atk);
	ImGui::NewLine();

	ImGui::Text("Defense");
	ImGui::InputScalar("Normal Defense", DT::ImGuiDataType_U16, &m.normal_def);
	ImGui::InputScalar("Fire Defense", DT::ImGuiDataType_U16, &m.fire_def);
	ImGui::InputScalar("Water Defense", DT::ImGuiDataType_U16, &m.water_def);
	ImGui::InputScalar("Thunder Defense", DT::ImGuiDataType_U16, &m.thunder_def);
	ImGui::InputScalar("Ice Defense", DT::ImGuiDataType_U16, &m.ice_def);
	ImGui::InputScalar("Dragon Defense", DT::ImGuiDataType_U16, &m.dragon_def);
	ImGui::NewLine();

	ImGui::InputScalar("HP Bonus", DT::ImGuiDataType_U8, &m.hp_bonus);
	ImGui::NewLine();

	ImGui::Text("Attack Bonus");
	ImGui::InputScalar("Normal Attack Bonus", DT::ImGuiDataType_U16, &m.normal_atk_bonus);
	ImGui::InputScalar("Fire Attack Bonus", DT::ImGuiDataType_U16, &m.fire_atk_bonus);
	ImGui::InputScalar("Water Attack Bonus", DT::ImGuiDataType_U16, &m.water_atk_bonus);
	ImGui::InputScalar("Thunder Attack Bonus", DT::ImGuiDataType_U16, &m.thunder_atk_bonus);
	ImGui::InputScalar("Ice Attack Bonus", DT::ImGuiDataType_U16, &m.ice_atk_bonus);
	ImGui::InputScalar("Dragon Attack Bonus", DT::ImGuiDataType_U16, &m.dragon_atk_bonus);
	ImGui::NewLine();

	ImGui::Text("Defense Bonus");
	ImGui::InputScalar("Normal Defense Bonus", DT::ImGuiDataType_U16, &m.normal_def_bonus);
	ImGui::InputScalar("Fire Defense Bonus", DT::ImGuiDataType_U16, &m.fire_def_bonus);
	ImGui::InputScalar("Water Defense Bonus", DT::ImGuiDataType_U16, &m.water_def_bonus);
	ImGui::InputScalar("Thunder Defense Bonus", DT::ImGuiDataType_U16, &m.thunder_def_bonus);
	ImGui::InputScalar("Ice Defense Bonus", DT::ImGuiDataType_U16, &m.ice_def_bonus);
	ImGui::InputScalar("Dragon Defense Bonus", DT::ImGuiDataType_U16, &m.dragon_def_bonus);
	ImGui::NewLine();

	if (show_unknowns)
	{
		ImGui::InputScalar("Unk0", DT::ImGuiDataType_S32, &m.unk);
		ImGui::InputScalarN("Unk2", DT::ImGuiDataType_U8, m.unk2, 2);
		ImGui::InputScalarN("Unk3", DT::ImGuiDataType_S32, m.unk3, 5);
		ImGui::InputScalar("Unk4", DT::ImGuiDataType_S16, &m.unk4);
		ImGui::InputScalarN("Unk5", DT::ImGuiDataType_S32, m.unk5, 11);
		ImGui::InputScalarN("Unk6", DT::ImGuiDataType_S32, m.unk6, 2);
		ImGui::InputScalar("Unk7", DT::ImGuiDataType_S32, &m.unk7);
		ImGui::InputScalarN("Unk8", DT::ImGuiDataType_U8, m.unk8, 3);
		ImGui::InputScalar("Unk9", DT::ImGuiDataType_S32, &m.unk9);
		ImGui::InputScalarN("Unk10", DT::ImGuiDataType_S32, m.unk10, 35);
		ImGui::InputScalarN("Unk11", DT::ImGuiDataType_S32, m.unk10, 11);
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
			if (ImGui::BeginCombo("Gene", gene_names[gene.gene_id]))
			{
				for (int i = 0; i < gene_names.size(); i++)
				{
					if (ImGui::Selectable(gene_names[i], i == gene.gene_id))
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

	if (ImGui::BeginCombo("Player", sd::players[selected_player].name))
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

	if (ImGui::BeginCombo("Equipment Type", eq_type.at(t.equipment_type)))
	{
		for (const auto& [id, name] : eq_type)
		{
			if (ImGui::Selectable(name, id == t.equipment_type))
			{
				t.equipment_type = id;
			}
		}

		ImGui::EndCombo();
	}

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
	
	ImGui::Checkbox("Equipped", &t.equipped);


	if (ImGui::BeginCombo("Skill 1", GetSkillName(t.skill1)))
	{
		if (ImGui::Selectable("Empty", t.skill1 == 0))
		{
			t.skill1 = 0;
		}

		for (int i = 0; i < skill_names.size(); i++)
		{
			u16 skl_id = i + 3000;

			if (ImGui::Selectable(skill_names[i], skl_id == t.skill1))
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

		for (int i = 0; i < skill_names.size(); i++)
		{
			u16 skl_id = i + 3000;

			if (ImGui::Selectable(skill_names[i], skl_id == t.skill2))
			{
				t.skill2 = skl_id;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::EndGroup();
}
