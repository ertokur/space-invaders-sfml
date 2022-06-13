#include "EnemyBulletMap.h"
#include <assert.h>

EnemyBulletMap* EnemyBulletMap::m_enemybullets = nullptr;

EnemyBulletMap::EnemyBulletMap(sf::Vector2u windowSize) : m_windowSize(windowSize) {
	assert(m_enemybullets == nullptr);
	m_enemybullets = this;
}

void EnemyBulletMap::add(GameObject& const g_object) {
	m_enemybullets->m_list.push_back(new GameObject(g_object));
}

bool EnemyBulletMap::is_over(GameObject* obj) {
	return (*obj).getPosition().y > (m_enemybullets->m_windowSize.y);
}

void EnemyBulletMap::update() {

	for (int i = 0; i < m_enemybullets->m_list.size(); i++) {
		sf::Vector2f pos = m_enemybullets->m_list[i]->getPosition();

		(*m_enemybullets->m_list[i]).setPosition(pos.x, pos.y + 5);

		if (is_over(m_enemybullets->m_list[i]))
			m_enemybullets->m_list.erase(m_enemybullets->m_list.begin() + i);
	}

}

void EnemyBulletMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& iter : m_enemybullets->m_list) {
		target.draw(*iter);
	}
}