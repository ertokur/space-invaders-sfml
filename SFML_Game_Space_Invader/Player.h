#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "AssetManager.h"

class Player : public GameObject {

public:
	Player(const int& shapeWidth, const int& shapeHeight, const sf::Texture& texture) :
		GameObject(shapeWidth, shapeHeight, texture),
		m_sound(AssetManager::getSoundBuffer("assets/sounds/ShipBullet.wav")) {}
	void processEvents(const int& windowWidth);

private:
	
	sf::Sound m_sound;
	bool m_isShooting = false;

	friend class Game;

};