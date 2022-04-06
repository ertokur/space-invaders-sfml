#include "AssetManager.h"
#include <assert.h>

AssetManager* AssetManager::m_instance = nullptr;

AssetManager::AssetManager() {
	assert(m_instance == nullptr);
	m_instance = this;
}

sf::Texture& AssetManager::getTexture(std::string const& fileName) {
	auto foundPair = m_instance->m_textures.find(fileName);
	if (foundPair != m_instance->m_textures.end())
		return foundPair->second;
	else {
		sf::Texture& tex = m_instance->m_textures[fileName];
		tex.loadFromFile(fileName);
		return tex;
	}
}

sf::SoundBuffer& AssetManager::getSoundBuffer(std::string const& fileName) {
	auto foundPair = m_instance->m_soundBuffers.find(fileName);
	if (foundPair != m_instance->m_soundBuffers.end())
		return foundPair->second;
	else {
		sf::SoundBuffer& sBuf = m_instance->m_soundBuffers[fileName];
		sBuf.loadFromFile(fileName);
		return sBuf;
	}
}