#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <assert.h>
#include <string>

#include <random>
#include <ctime>

using namespace sf;

Game::Game(const int& windowWidth, const int& windowHeight, const int& fps) :

	m_mainWindow(VideoMode(windowWidth, windowHeight), "Space Invaders", Style::Titlebar | Style::Close),
	m_player(60, 32, manager.getTexture("assets/images/Ship.png")),
	m_stars(150, 1, 5, m_mainWindow.getSize())
{

	m_mainWindow.setFramerateLimit(fps);
	ImGui::SFML::Init(m_mainWindow);

	m_player.setPosition(windowWidth / 2, windowHeight - 32);


	//Set window icon
	Image img;
	bool imgNotExists = img.loadFromFile("assets/images/RedInvader.png");
	assert(imgNotExists);
	m_mainWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());


}

int Game::drawMenu()
{
	Clock _clock;

	do
	{
		sf::Event event;

		while (m_mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				m_mainWindow.close();
				return 0;
			}

			ImGui::SFML::ProcessEvent(event);
		}

		ImGui::SFML::Update(m_mainWindow, _clock.restart());

		ImGui::Begin("Main menu");

		ImGui::PushItemWidth(ImGui::GetWindowSize().x * 0.5f);

		if (ImGui::Button("Play", ImVec2(-1.0f, 0.0f)))
			return 1;

		if (ImGui::Button("Best results", ImVec2(-1.0f, 0.0f)))
			return 2;

		if (ImGui::Button("Exit", ImVec2(-1.0f, 0.0f)))
			return 3;

		ImGui::End();

		m_mainWindow.clear();
		ImGui::SFML::Render(m_mainWindow);
		m_mainWindow.draw(m_stars);
		m_mainWindow.display();

	} while (true);

	ImGui::SFML::Shutdown();
}


void Game::run() 
{

	do {
		int choice = drawMenu();

		switch (choice)
		{
		case 1:
			m_stars.updatePositions();

			while (m_mainWindow.isOpen())
			{

				processEvents();
				updateAll();
				renderAll();

			}

			/// <summary>
			/// сделать выход
			/// </summary>

			break;

		case 2:


			break;

		case 3:
			return;
		}

	} while (true);

	

	
	
}

bool Game::enemiesOver() 
{
	for (int i = 0; i < 10; i++)
		if (!enemies.m_objects[i].empty())
			return false;

	return true;
}

void Game::processEvents() 
{

	Event _event;

	while (m_mainWindow.pollEvent(_event)) {
		
		ImGui::SFML::ProcessEvent(_event);

		if (_event.type == Event::Closed)
			m_mainWindow.close();

		if (_event.type == Event::KeyPressed)
		{

			if (_event.key.code == Keyboard::E || _event.key.code == Keyboard::Space) 
			{
				m_player.m_isShooting = true;
			}
		}

	}

	m_player.processEvents(m_mainWindow.getSize().x);

}

void Game::updateAll()
{

	for (int i = 0; i < bullets.m_list.size(); i++) {

		auto& bullet = bullets.m_list[i];

		for (int j = 0; j < 10; j++) {

			if (enemies.m_objects[j].empty())
				continue;

			auto& enemy = enemies.m_objects[j].back();

			if (enemy->getBound().intersects(bullet->getBound())) {
				bullets.m_list.erase(bullets.m_list.begin() + i);
				enemies.m_objects[j].pop_back();
				enemies.m_sound.play();

				totalScore += 10 * (7 - enemies.m_objects[j].size());
			}
		}
	}

	bullets.update();

	if (m_player.m_isShooting) 
	{
		GameObject temp(6, 17, manager.getTexture("assets/images/Bullet.png"));

		temp.setOrigin(3, 17);
		temp.setPosition(m_player.getPosition().x, m_player.getPosition().y);

		bullets.add(temp);

		m_player.m_isShooting = false;
		m_player.m_sound.play();
	}

	m_stars.update();
}

void Game::renderAll()
{


	m_mainWindow.clear();
	m_mainWindow.draw(m_stars);

	m_mainWindow.draw(enemies);
	m_mainWindow.draw(m_player);
	
	m_mainWindow.draw(bullets);
	
	Font _font;
	_font.loadFromFile("assets/fonts/unifont.ttf");
	Text _score(std::to_string(totalScore), _font, 40);
	_score.setPosition(20,10);

	m_mainWindow.draw(_score);

	m_mainWindow.display();

}