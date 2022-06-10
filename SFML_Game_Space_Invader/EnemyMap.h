#pragma once
#include "GameObject.h"
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class EnemyMap: public sf::Drawable {

private:
	std::vector<std::list<GameObject*>> m_objects{ 10 };
	sf::Sound m_sound;
	static EnemyMap* m_enemies;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	EnemyMap();
	
	friend class Game;
};