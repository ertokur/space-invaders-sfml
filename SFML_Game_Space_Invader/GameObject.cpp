#include "GameObject.h"
#include <SFML/Graphics.hpp>	
using namespace sf;

GameObject::GameObject(const int& shapeWidth, const int& shapeHeight, const Texture& texture):
m_shape(Vector2f(shapeWidth, shapeHeight)), m_tex(texture) {

	m_shape.setTexture(&m_tex);
	m_shape.setOrigin(shapeWidth / 2, shapeHeight / 2);

}

FloatRect GameObject::getBound() {
	return m_shape.getGlobalBounds();
}

void GameObject::setPosition(const int& x, const int& y) {
	m_shape.setPosition(x, y);
}

Vector2f GameObject::getPosition() const {
	return m_shape.getPosition();
}

void GameObject::setOrigin(const int& x, const int& y) {
	m_shape.setOrigin(x, y);
}

void GameObject::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_shape);
}