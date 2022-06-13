#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <list>

class EnemyBulletMap :public sf::Drawable, public GameObject {

private:
	std::vector<GameObject*> m_list;
	sf::Vector2u m_windowSize;
	static EnemyBulletMap* m_enemybullets;
	
	static bool is_over(GameObject* obj);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	EnemyBulletMap(sf::Vector2u windowSize);
	static void add(GameObject& const g_object);
	static void update();

	friend class Game;
};