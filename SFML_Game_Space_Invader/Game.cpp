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
	//Ограничиваем FPS (кадры в секунду)
	m_mainWindow.setFramerateLimit(fps);
	
	m_player.setPosition(windowWidth / 2, windowHeight - 32);

	//Устанавливаем иконку
	Image img;
	bool imgNotExists = img.loadFromFile("assets/images/RedInvader.png");
	assert(imgNotExists);
	m_mainWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

void errorMessage()
{
	cout << "---" << endl;
	cout << "Введены неверные входные данные!" << endl;
	cout << "Повторите попытку!" << endl;
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


//Отрисовка главного меню
void Game::drawMainMenu(int& result)
{
	cout << "+--------------------+" << endl;
	cout << "|    ГЛАВНОЕ МЕНЮ    |" << endl;
	cout << "+--------------------+" << endl;
	cout << "|Играть           (1)|" << endl;
	cout << "|Таблица рекордов (2)|" << endl;
	cout << "|Выйти            (0)|" << endl;
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

	//Выпускаем пулю противника каждую 1 секунду
	if (clock.getElapsedTime().asSeconds() > 1 && !gameEnded)
	{
		//Перезапускаем таймер
		clock.restart();
		createNewEnemyBullet();
	}

	//Проверка пересечения пули игрока и корабля противника
	for (int i = 0; i < bullets.m_list.size(); i++) 
	{
		auto& bullet = bullets.m_list[i];

		for (int j = 0; j < 10; j++) 
		{
			if (enemies.m_objects[j].empty())
				continue;

			auto& enemy = enemies.m_objects[j].back();

			//Если пуля и корабль противника пересеклись
			if (enemy->getBound().intersects(bullet->getBound())) 
			{
				//Убираем пулю из массива
				bullets.m_list.erase(bullets.m_list.begin() + i);
				//Убираем противника
				enemies.m_objects[j].pop_back();
				//Воспроизведение звука взрыва
				enemies.m_sound.play();
				//Прибавляем очки
				totalScore += 10 * (7 - enemies.m_objects[j].size());
			}
		}
	}

	//Проверка пересечения пули врага и корабля игрока
	for (int i = 0; i < enemy_bullets.m_list.size(); i++)
	{
		//Если пуля и корабль игрока пересеклись
		if (m_player.getBound().intersects(enemy_bullets.m_list[i]->getBound()))
		{
			//Воспроизведение звука взрыва
			enemies.m_sound.play();
			//Убираем пулю из массива
			enemy_bullets.m_list.erase(enemy_bullets.m_list.begin() + i);
			//Уменьшаем кол-во жизней
			--lifesCount;
		}
	}

	//Если игрок нажал на кнопку стрелять, то
	//выпускаем пулю
	if (m_player.m_isShooting) 
	{
		GameObject temp(6, 17, manager.getTexture("assets/images/Bullet.png"));

		temp.setOrigin(3, 17);
		temp.setPosition(m_player.getPosition().x, m_player.getPosition().y);

		//Добавляем новый объект в массив
		bullets.add(temp);

		m_player.m_isShooting = false;
		//Воспроизводим звук выстрела
		m_player.m_sound.play();
	}

	//Обновляем движение пуль игрока
	bullets.update();
	//Обновляем движение пуль противника
	enemy_bullets.update();
	//Обновляем движение звезд на заднем фоне
	m_stars.update();
}

//Отрисовка всех объектов на экране
void Game::renderAll()
{
	m_mainWindow.clear();
	//Загружаем шрифт
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
	//Звезды на заднем фоне
	m_mainWindow.draw(m_stars);
	//Корабли игрока и противника
	m_mainWindow.draw(enemies);
	m_mainWindow.draw(m_player);
	//Пули игрока и противника
	m_mainWindow.draw(bullets);
	m_mainWindow.draw(enemy_bullets);
	
	//Поле, отображающее кол-во очков
	Text _score(std::to_string(totalScore), _font, 40);
	_score.setPosition(20,10);
	//Поле, отображающее кол-во жизней
	Text _lifes(std::to_string(lifesCount), _font, 40);
	_lifes.setPosition(m_mainWindow.getSize().x - 40, 10);
	//Их отрисовка
	m_mainWindow.draw(_score);
	m_mainWindow.draw(_lifes);
	//Иконка сердца
	GameObject heart(48, 48, manager.getTexture("assets/images/heart.png"));
	heart.setPosition(m_mainWindow.getSize().x - 70, 36);
	m_mainWindow.draw(heart);

	m_mainWindow.display();
}