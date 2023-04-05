#include "WinWindow.h"

WinWindow::WinWindow(sf::RenderWindow &window): window(window)
{
	background = sf::RectangleShape(sf::Vector2f(300.f, 600.f));
	background.setPosition(250, 100);

	background.setFillColor(sf::Color(47, 79, 79));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);

	button = sf::RectangleShape(sf::Vector2f(200.f, 100.f));
	button.setPosition(300, 300);
	button.setFillColor(sf::Color(181, 154, 84));
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(2.f);

	font.loadFromFile("font.otf");

	text.setFont(font);
	text.setString("White wins");
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::Black);
	text.setPosition(325,150);

	text2.setFont(font);
	text2.setString("New game");
	text2.setCharacterSize(28);
	text2.setFillColor(sf::Color::Black);
	text2.setPosition(335, 330);


}

void WinWindow::display() 
{
	if (show) 
	{
		window.draw(background);
		window.draw(text);
		window.draw(button);
		window.draw(text2);
	}
}

void WinWindow::set(Color color) 
{
	if (color == Color::black) 
	{
		text.setString("White wins");
	}
	else 
	{
		text.setString("Black wins");
	}
}