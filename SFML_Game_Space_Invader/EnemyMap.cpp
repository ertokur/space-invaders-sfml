#include "EnemyMap.h"
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "Game.h"

EnemyMap* EnemyMap::m_enemies = nullptr;

EnemyMap::EnemyMap():m_sound(AssetManager::getSoundBuffer("assets/sounds/ShipHit.wav")) {

	assert(m_enemies == nullptr);
	m_enemies = this;

	sf::Texture A2 = AssetManager::getTexture("assets/images/InvaderA2.png");
	sf::Texture B2 = AssetManager::getTexture("assets/images/InvaderB2.png");
	sf::Texture C2 = AssetManager::getTexture("assets/images/InvaderC2.png");

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++)
			m_enemies->m_objects[i].push_back(new GameObject(60, 35, A2, i * 80 + 40, j * 50 + 50));
		for (int j = 3; j < 6; j++)
			m_enemies->m_objects[i].push_back(new GameObject(60, 35, C2, i * 80 + 40, j * 50 + 50));
		m_enemies->m_objects[i].push_back(new GameObject(60, 35, B2, i * 80 + 40, 350));
	}

}

void EnemyMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& iter1 : m_enemies->m_objects)
		for (const auto& iter2 : iter1)
			target.draw(*iter2);
}