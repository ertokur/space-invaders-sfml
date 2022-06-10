#include "Player.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void Player::processEvents(const int& windowWidth) 
{

	if (m_shape.getPosition().x < 30)
		m_shape.setPosition(windowWidth - 30, m_shape.getPosition().y);

	if (m_shape.getPosition().x > windowWidth - 30)
		m_shape.setPosition(30, m_shape.getPosition().y);

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		m_shape.move(-5, 0);

	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		m_shape.move(5, 0);

}