#pragma once
#include "SFML/Graphics.hpp"
#include "Figure.h"
class WinWindow
{
public:
	WinWindow(sf::RenderWindow &window);
	sf::RenderWindow &window;
	sf::RectangleShape button;
	void display();
	bool show = false;
	void set(Color color);
private:
	sf::RectangleShape background;
	sf::Text text;
	sf::Text text2;
	sf::Font font;
};

