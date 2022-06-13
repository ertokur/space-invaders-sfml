#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "AssetManager.h"
#include "EnemyMap.h"
#include "BulletMap.h"
#include "EnemyBulletMap.h"
#include "BackgroundStars.h"

class Game
{
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
	EnemyBulletMap   enemy_bullets;

	Player m_player;
	
	BackgroundStars m_stars;

	int totalScore = 0;
	int lifesCount = 1;
	bool gameEnded = false;

	void processEvents();
	void updateAll(sf::Clock &clock);
	void renderAll();

	bool enemiesOver();

	void createNewEnemyBullet();

	void drawMainMenu(int& result);
	void drawHighScoreForm();
};