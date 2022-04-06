#include "Game.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>
#include "Player.h"
using namespace sf;

Game::Game(const int& windowWidth, const int& windowHeight, const int& fps) :

	m_mainWindow(VideoMode(windowWidth, windowHeight), "Space Invaders", Style::Titlebar | Style::Close),
	m_player(60, 32, manager.getTexture("assets/images/Ship.png"))
{

	m_mainWindow.setFramerateLimit(fps);

	m_player.setPosition(windowWidth / 2, windowHeight - 32);


	//Set window icon
	Image img;
	bool imgNotExists = img.loadFromFile("assets/images/RedInvader.png");
	assert(imgNotExists);
	m_mainWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

}

void Game::run() {

	Clock _clock;
	Font _font;
	bool fontFound = _font.loadFromFile("assets/fonts/unifont.ttf");
	assert(fontFound);
	Text _text("Control: A/D/Arrows - move, E/Space - attack\nEscape - quitn\n\nTokursky 2022", _font, 32);
	_text.setFillColor(Color::Green);
	

	while (_clock.getElapsedTime() <= seconds(2)) {
		processEvents();
		m_mainWindow.clear();
		m_mainWindow.draw(_text);
		m_mainWindow.display();
	}

	Time currentFrameTime = Time::Zero;

	while (m_mainWindow.isOpen()) {
		currentFrameTime = _clock.restart();
		processEvents();
		updateAll();
		renderAll();
		std::cout << "FPS: " << 1.0f / currentFrameTime.asSeconds() << std::endl;
	}

}

bool Game::enemiesOver() {
	for (int i = 0; i < 10; i++)
		if (!enemies.m_objects[i].empty())
			return false;
	return true;
}

void Game::processEvents() {

	Event _event;
	while (m_mainWindow.pollEvent(_event)) {
		if (_event.type == Event::Closed)
			m_mainWindow.close();

		if (_event.type == Event::KeyPressed) {
			if (_event.key.code == Keyboard::Escape)
				m_mainWindow.close();
			if (_event.key.code == Keyboard::E || _event.key.code == Keyboard::Space)
				m_player.m_isShooting = true;
		}
	}

	m_player.processEvents(m_mainWindow.getSize().x);

}

void Game::updateAll() {

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
			}
		}
	}

	bullets.update();

	if (m_player.m_isShooting) {
		GameObject temp(6, 17, manager.getTexture("assets/images/Bullet.png"));
		temp.setOrigin(3, 17);
		temp.setPosition(m_player.getPosition().x, m_player.getPosition().y);
		bullets.add(temp);
		m_player.m_isShooting = false;
		m_player.m_sound.play();
	}

}

void Game::renderAll() {

	m_mainWindow.clear();
	if (enemiesOver()) {
		Font _font;
		bool fontFound = _font.loadFromFile("assets/fonts/unifont.ttf");
		assert(fontFound);

		Text _finalMessage("POSHEL NAXUI", _font, 96);
		_finalMessage.setFillColor(Color::Green);
		FloatRect textRect = _finalMessage.getLocalBounds();
		_finalMessage.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		Vector2u screenSize = m_mainWindow.getSize();
		_finalMessage.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

		m_mainWindow.draw(_finalMessage);
	}
	m_mainWindow.draw(enemies);
	m_mainWindow.draw(m_player);
	m_mainWindow.draw(bullets);
	m_mainWindow.display();

}