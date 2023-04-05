#pragma once
#include "SFML/Graphics.hpp"
#include "figure.h"
class Menu
{
public:
	Menu(sf::RenderWindow & window);
	sf::RenderWindow & window;
	sf::RectangleShape reset_button;
	sf::RectangleShape undo_button;
	sf::RectangleShape redo_button;

	void display();
	void set();
private:
	sf::RectangleShape background;
	sf::RectangleShape player;
	sf::Text reset_text;
	sf::Text undo_text;
	sf::Text redo_text;
	sf::Text move_text;
	sf::Font font;
};

