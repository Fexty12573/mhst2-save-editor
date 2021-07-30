
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include <Windows.h>

#include "setup.h"
#include "draw.h"

#include "dependencies/Vec2.h"
#include "dependencies/SFColor.h"

int main(int argc, char* argv[])
{
	FreeConsole();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Monster Hunter Stories 2 Save Editor", sf::Style::Default);
	sf::Clock clock;

	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	ImGui::StyleColorsLight();
	ImGui::svSetFont("./fonts/TCM_____.ttf");
	ImGui::svSetupLightTheme();

	while (window.isOpen())
	{
		auto dt = clock.restart();

		sf::Event evt;
		while (window.pollEvent(evt))
		{
			ImGui::SFML::ProcessEvent(evt);

			switch (evt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		ImGui::SFML::Update(window, dt);

		ImGui::svBegin("window", window);
		DrawMainWindow();
		ImGui::svEnd();

		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	return 0;
}
