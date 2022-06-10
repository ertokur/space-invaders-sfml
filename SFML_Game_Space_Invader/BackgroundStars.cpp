#include "BackgroundStars.h"

BackgroundStars::BackgroundStars(unsigned int count, unsigned int radius, unsigned int speed, sf::Vector2u windowSize)
	: m_count(count), m_radius(radius), m_speed(speed), m_windowSize(windowSize)
{
	srand(time(NULL));

	sf::CircleShape temp(m_radius, m_radius * 4);

	for (unsigned int i = 0; i < m_count; i++)
	{
		sf::Color clr(rand() % 256, rand() % 256, rand() % 256);

		temp.setPosition(std::rand() % m_windowSize.x, std::rand() % m_windowSize.y);
		temp.setFillColor(clr);

		circles.push_back(temp);
	}
}

void BackgroundStars::updatePositions()
{
	srand(time(NULL));

	for (unsigned int i = 0; i < m_count; i++)
	{
		circles[i].setPosition(std::rand() % m_windowSize.x, std::rand() % m_windowSize.y);
	}
}

void BackgroundStars::update()
{
	srand(time(NULL));

	for (unsigned int i = 0; i < m_count; i++)
	{
		sf::Vector2f currentPos = circles[i].getPosition();
		if (currentPos.y >= m_windowSize.y)
			circles[i].setPosition(currentPos.x, 0);
		else
			circles[i].setPosition(currentPos.x, currentPos.y + rand() % m_speed);
	}
}

void BackgroundStars::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& circle : circles)
		target.draw(circle);
}