#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "AssetManager.h"
#include "EnemyMap.h"
#include "BulletMap.h"

class Game {

public:
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;

	Game(const int& windowHeight, const int& windowWidth, const int& fps);
	void run();

private:
	sf::RenderWindow m_mainWindow;

	AssetManager     manager;
	EnemyMap         enemies;
	BulletMap        bullets;

	Player m_player;

	void processEvents();
	void updateAll();
	void renderAll();
	bool enemiesOver();

};