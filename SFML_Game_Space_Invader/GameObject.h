#pragma once
#include <SFML/Graphics.hpp>

class GameObject: public sf::Drawable {
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	explicit GameObject() = default;
	explicit GameObject(const int& shapeWidth, const int& shapeHeight, const sf::Texture& texture);

	explicit GameObject(const int& shapeWidth, const int& shapeHeight, const sf::Texture& texture,
		const int& x, const int& y) :
		GameObject(shapeWidth, shapeHeight, texture) { setPosition(x, y); }

	sf::FloatRect getBound();
	void setPosition(const int& x, const int& y);
	sf::Vector2f getPosition() const;
	void setOrigin(const int& x, const int& y);

protected:
	sf::Texture m_tex;
	sf::RectangleShape m_shape;
	
};