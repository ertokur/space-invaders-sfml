#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

#include "imgui.h"
#include "imgui-SFML.h"

int main() {

	Game game(800, 600, 60);
	game.run();

	return EXIT_SUCCESS;
}