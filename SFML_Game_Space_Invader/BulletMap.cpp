#include "BulletMap.h"
#include <assert.h>

BulletMap* BulletMap::m_bullets = nullptr;

BulletMap::BulletMap() {
	assert(m_bullets == nullptr);
	m_bullets = this;
}

void BulletMap::add(GameObject& const g_object) {
	m_bullets->m_list.push_back(new GameObject(g_object));
}

bool BulletMap::is_over(GameObject* obj) {
	return (*obj).getPosition().y < 0;
}

void BulletMap::update() {
	
	for (int i = 0; i < m_bullets->m_list.size(); i++) 
	{
		sf::Vector2f pos = m_bullets->m_list[i]->getPosition();

		(*m_bullets->m_list[i]).setPosition(pos.x, pos.y - 10);

		if (is_over(m_bullets->m_list[i]))
			m_bullets->m_list.erase(m_bullets->m_list.begin() + i);
	}

}

void BulletMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& iter : m_bullets->m_list) {
		target.draw(*iter);
	}
}