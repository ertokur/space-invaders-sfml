#include "Game.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <string>
#include <random>
#include <ctime>

using namespace sf;
using namespace std;

Game::Game(const int& windowWidth, const int& windowHeight, const int& fps) :
	m_mainWindow(VideoMode(windowWidth, windowHeight), "Space Invaders", Style::Titlebar | Style::Close),
	m_player(60, 32, manager.getTexture("assets/images/Ship.png")),
	m_stars(150, 1, 5, m_mainWindow.getSize()),
	enemy_bullets(m_mainWindow.getSize())
{
	//������������ FPS (����� � �������)
	m_mainWindow.setFramerateLimit(fps);
	
	m_player.setPosition(windowWidth / 2, windowHeight - 32);

	//������������� ������
	Image img;
	bool imgNotExists = img.loadFromFile("assets/images/RedInvader.png");
	assert(imgNotExists);
	m_mainWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

void errorMessage()
{
	cout << "---" << endl;
	cout << "������� �������� ������� ������!" << endl;
	cout << "��������� �������!" << endl;
	cout << "---" << endl;
	system("pause");
	cin.clear();
	cin.ignore(100, '\n');
}


void Game::run() 
{
	Clock _clock;
	int choice;

	do {
		drawMainMenu(choice);
		switch (choice)
		{
		case 1:
			m_stars.updatePositions();
			totalScore = 0;
			gameEnded = false;
			lifesCount = 1;

			while (m_mainWindow.isOpen())
			{
				processEvents();
				updateAll(_clock);
				renderAll();
			}

			break;

		case 2:


			break;

		case 3:
			return;

		default:
			errorMessage();
		}

	} while (m_mainWindow.isOpen());

}


//��������� �������� ����
void Game::drawMainMenu(int& result)
{
	cout << "+--------------------+" << endl;
	cout << "|    ������� ����    |" << endl;
	cout << "+--------------------+" << endl;
	cout << "|������           (1)|" << endl;
	cout << "|������� �������� (2)|" << endl;
	cout << "|�����            (0)|" << endl;
	cout << "+--------------------+" << endl;
	cout << ">> ";
	if (!(cin >> result))
		result = -1;
}

void Game::drawHighScoreForm()
{

}

bool Game::enemiesOver() 
{
	for (int i = 0; i < 10; i++)
		if (!enemies.m_objects[i].empty())
			return false;

	return true;
}

void Game::createNewEnemyBullet()
{
	int index;

	do {
		index = std::rand() % 10;
	} while (enemies.m_objects[index].empty());

	auto& enemy = enemies.m_objects[index].back();

	GameObject temp(6, 17, manager.getTexture("assets/images/Bullet.png"));

	temp.setOrigin(3, 17);
	temp.setPosition(enemy->getPosition().x, enemy->getPosition().y);

	enemy_bullets.add(temp);

	m_player.m_sound.play();
}

void Game::processEvents() 
{

	Event _event;

	while (m_mainWindow.pollEvent(_event)) 
	{

		if (_event.type == Event::Closed)
			m_mainWindow.close();

		if (_event.type == Event::KeyPressed)
		{
			if ((_event.key.code == Keyboard::E || _event.key.code == Keyboard::Space) && !gameEnded)
			{
				m_player.m_isShooting = true;
			}
		}

	}
	
	m_player.processEvents(m_mainWindow.getSize().x);

}

void Game::updateAll(Clock &clock)
{
	std::srand(time(NULL));

	if (lifesCount == 0)
		gameEnded = true;

	if (enemiesOver())
		gameEnded = true;

	//��������� ���� ���������� ������ 1 �������
	if (clock.getElapsedTime().asSeconds() > 1 && !gameEnded)
	{
		//������������� ������
		clock.restart();
		createNewEnemyBullet();
	}

	//�������� ����������� ���� ������ � ������� ����������
	for (int i = 0; i < bullets.m_list.size(); i++) 
	{
		auto& bullet = bullets.m_list[i];

		for (int j = 0; j < 10; j++) 
		{
			if (enemies.m_objects[j].empty())
				continue;

			auto& enemy = enemies.m_objects[j].back();

			//���� ���� � ������� ���������� �����������
			if (enemy->getBound().intersects(bullet->getBound())) 
			{
				//������� ���� �� �������
				bullets.m_list.erase(bullets.m_list.begin() + i);
				//������� ����������
				enemies.m_objects[j].pop_back();
				//��������������� ����� ������
				enemies.m_sound.play();
				//���������� ����
				totalScore += 10 * (7 - enemies.m_objects[j].size());
			}
		}
	}

	//�������� ����������� ���� ����� � ������� ������
	for (int i = 0; i < enemy_bullets.m_list.size(); i++)
	{
		//���� ���� � ������� ������ �����������
		if (m_player.getBound().intersects(enemy_bullets.m_list[i]->getBound()))
		{
			//��������������� ����� ������
			enemies.m_sound.play();
			//������� ���� �� �������
			enemy_bullets.m_list.erase(enemy_bullets.m_list.begin() + i);
			//��������� ���-�� ������
			--lifesCount;
		}
	}

	//���� ����� ����� �� ������ ��������, ��
	//��������� ����
	if (m_player.m_isShooting) 
	{
		GameObject temp(6, 17, manager.getTexture("assets/images/Bullet.png"));

		temp.setOrigin(3, 17);
		temp.setPosition(m_player.getPosition().x, m_player.getPosition().y);

		//��������� ����� ������ � ������
		bullets.add(temp);

		m_player.m_isShooting = false;
		//������������� ���� ��������
		m_player.m_sound.play();
	}

	//��������� �������� ���� ������
	bullets.update();
	//��������� �������� ���� ����������
	enemy_bullets.update();
	//��������� �������� ����� �� ������ ����
	m_stars.update();
}

//��������� ���� �������� �� ������
void Game::renderAll()
{
	m_mainWindow.clear();
	//��������� �����
	Font _font;
	_font.loadFromFile("assets/fonts/unifont.ttf");

	if (gameEnded)
	{
		Text text("", _font, 96);
		text.setPosition(m_mainWindow.getSize().x / 2, m_mainWindow.getSize().y / 2);
		text.setOrigin(m_mainWindow.getSize().x / 2, m_mainWindow.getSize().y / 2);

		if (lifesCount == 0)
		{
			text.setFillColor(Color::Red);
			text.setString("YOU LOSE");
		}
		else
		{
			text.setFillColor(Color::Green);
			text.setString("YOU WIN");
		}
		
		m_mainWindow.draw(text);
		m_mainWindow.draw(m_stars);
		m_mainWindow.display();
		return;
	}
	//������ �� ������ ����
	m_mainWindow.draw(m_stars);
	//������� ������ � ����������
	m_mainWindow.draw(enemies);
	m_mainWindow.draw(m_player);
	//���� ������ � ����������
	m_mainWindow.draw(bullets);
	m_mainWindow.draw(enemy_bullets);
	
	//����, ������������ ���-�� �����
	Text _score(std::to_string(totalScore), _font, 40);
	_score.setPosition(20,10);
	//����, ������������ ���-�� ������
	Text _lifes(std::to_string(lifesCount), _font, 40);
	_lifes.setPosition(m_mainWindow.getSize().x - 40, 10);
	//�� ���������
	m_mainWindow.draw(_score);
	m_mainWindow.draw(_lifes);
	//������ ������
	GameObject heart(48, 48, manager.getTexture("assets/images/heart.png"));
	heart.setPosition(m_mainWindow.getSize().x - 70, 36);
	m_mainWindow.draw(heart);

	m_mainWindow.display();
}