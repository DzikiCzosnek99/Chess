#pragma once
#include "SFML/Graphics.hpp"
#include "figure.h"
#include "string";
class Promotion
{
public:
	Promotion(sf::RenderWindow &window, sf::Vector2f position);
	sf::Vector2f position{};
	Color color{};
	sf::RenderWindow &window;

	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;

	sf::Sprite choice1;
	sf::Sprite choice2;
	sf::Sprite choice3;
	sf::Sprite choice4;

	std::string path1;
	std::string path2;
	std::string path3;
	std::string path4;

	sf::RectangleShape main;
	sf::RectangleShape background1;
	sf::RectangleShape background2;
	sf::RectangleShape background3;
	sf::RectangleShape background4;

	bool show = false;
	void display();
	void set(Color color);

};

