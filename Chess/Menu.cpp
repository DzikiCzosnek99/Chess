#include "Menu.h"

Menu::Menu(sf::RenderWindow &window) : window(window) 
{
	background = sf::RectangleShape(sf::Vector2f(300.f, 800.f));
	background.setPosition(800, 0);

	background.setFillColor(sf::Color(47, 79, 79));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);

	reset_button = sf::RectangleShape(sf::Vector2f(200.f, 75.f));
	reset_button.setPosition(850, 300);
	reset_button.setFillColor(sf::Color(181, 154, 84));
	reset_button.setOutlineColor(sf::Color::Black);
	reset_button.setOutlineThickness(2.f);

	undo_button = sf::RectangleShape(sf::Vector2f(90.f, 75.f));
	undo_button.setPosition(850, 400);
	undo_button.setFillColor(sf::Color(181, 154, 84));
	undo_button.setOutlineColor(sf::Color::Black);
	undo_button.setOutlineThickness(2.f);

	redo_button = sf::RectangleShape(sf::Vector2f(90.f, 75.f));
	redo_button.setPosition(960, 400);
	redo_button.setFillColor(sf::Color(181, 154, 84));
	redo_button.setOutlineColor(sf::Color::Black);
	redo_button.setOutlineThickness(2.f);

	player = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	player.setPosition(860, 250);
	player.setFillColor(sf::Color::Transparent);
	player.setOutlineThickness(8.f);

	player.setOutlineColor(sf::Color::White);
	


	font.loadFromFile("font.otf");

	reset_text.setFont(font);
	reset_text.setString("Reset");
	reset_text.setCharacterSize(28);
	reset_text.setFillColor(sf::Color::Black);
	reset_text.setPosition(910, 315);

	undo_text.setFont(font);
	undo_text.setString("<");
	undo_text.setCharacterSize(80);
	undo_text.setFillColor(sf::Color::Black);
	undo_text.setPosition(875, 365);

	redo_text.setFont(font);
	redo_text.setString(">");
	redo_text.setCharacterSize(80);
	redo_text.setFillColor(sf::Color::Black);
	redo_text.setPosition(985, 365);

	move_text.setFont(font);
	move_text.setCharacterSize(24);
	move_text.setPosition(900, 240);

	move_text.setString("white's move");
	move_text.setFillColor(sf::Color::White);
	
}

void Menu::display() 
{
	window.draw(background);
	window.draw(reset_button);
	window.draw(reset_text);
	window.draw(undo_button);
	window.draw(undo_text);
	window.draw(redo_button);
	window.draw(redo_text);
	window.draw(player);
	window.draw(move_text);
}

void Menu::set() 
{
	if (move_text.getFillColor() == sf::Color::White) 
	{
		player.setOutlineColor(sf::Color::Black);
		move_text.setString("black's move");
		move_text.setFillColor(sf::Color::Black);
	}
	else
	{
		player.setOutlineColor(sf::Color::White);
		move_text.setString("white's move");
		move_text.setFillColor(sf::Color::White);
	}
}

