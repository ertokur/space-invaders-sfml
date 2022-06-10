#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <random>

class BackgroundStars : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	std::vector<sf::CircleShape> circles;
	unsigned int m_radius = 0;
	unsigned int m_count = 0;
	unsigned int m_speed = 0.0f;
	sf::Vector2u m_windowSize;

public:

	BackgroundStars() = delete;
	BackgroundStars(unsigned int count, unsigned int radius, unsigned int speed, sf::Vector2u windowSize);

	void update();
	void updatePositions();
};

