#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager {

public:
	AssetManager();
	static sf::Texture& getTexture(std::string const& fileName);
	static sf::SoundBuffer& getSoundBuffer(std::string const& fileName);

private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	static AssetManager* m_instance;
	friend class Game;
};