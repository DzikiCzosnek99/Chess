#include "promotion.h"
Promotion::Promotion(sf::RenderWindow &window,sf::Vector2f position) :
	window(window), position(position), color(color) 
{
	
	main = sf::RectangleShape(sf::Vector2f(154.f, 604.f));
	main.setFillColor(sf::Color::Black);
	main.setPosition(position.x-2,position.y-2);

	background1 = sf::RectangleShape(sf::Vector2f(150.f, 150.f));
	background1.setFillColor(sf::Color(11, 111, 41));
	background1.setPosition(position);

	background2 = sf::RectangleShape(sf::Vector2f(150.f, 150.f));
	background2.setFillColor(sf::Color::White);
	background2.setPosition(position.x, position.y + 150);

	background3 = sf::RectangleShape(sf::Vector2f(150.f, 150.f));
	background3.setFillColor(sf::Color(11, 111, 41));
	background3.setPosition(position.x, position.y + 300);

	background4 = sf::RectangleShape(sf::Vector2f(150.f, 150.f));
	background4.setFillColor(sf::Color::White);
	background4.setPosition(position.x, position.y + 450);

	choice1.setPosition(position);
	choice2.setPosition(position.x, position.y + 150);
	choice3.setPosition(position.x, position.y + 300);
	choice4.setPosition(position.x, position.y + 450);
	
}

void Promotion::display() 
{
	if (show) 
	{
		window.draw(main);
		window.draw(background1);
		window.draw(background2);
		window.draw(background3);
		window.draw(background4);

		window.draw(choice1);
		window.draw(choice2);
		window.draw(choice3);
		window.draw(choice4);
	}
	
}

void Promotion::set(Color color) 
{
	if (color == Color::black)
	{
		path1 = "textures/hetman_czarny.png";
		path2 = "textures/wieza_czarna.png";
		path3 = "textures/goniec_czarny.png";
		path4 = "textures/skoczek_czarny.png";


	}
	else
	{

		path1 = "textures/hetman_bialy.png";
		path2 = "textures/wieza_biala.png";
		path3 = "textures/goniec_bialy.png";
		path4 = "textures/skoczek_bialy.png";


	}

	sf::Vector2f targetSize(150.0f, 150.0f);

	texture1.loadFromFile(path1);
	texture2.loadFromFile(path2);
	texture3.loadFromFile(path3);
	texture4.loadFromFile(path4);

	choice1.setTexture(texture1);
	choice2.setTexture(texture2);
	choice3.setTexture(texture3);
	choice4.setTexture(texture4);

	choice1.setScale(targetSize.x / choice1.getLocalBounds().width, targetSize.y / choice1.getLocalBounds().height);
	choice2.setScale(targetSize.x / choice2.getLocalBounds().width, targetSize.y / choice2.getLocalBounds().height);
	choice3.setScale(targetSize.x / choice3.getLocalBounds().width, targetSize.y / choice3.getLocalBounds().height);
	choice4.setScale(targetSize.x / choice4.getLocalBounds().width, targetSize.y / choice4.getLocalBounds().height);
}


