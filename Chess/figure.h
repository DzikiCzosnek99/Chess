#pragma once
#include "SFML/Graphics.hpp"
#include "string"
#include "array"
#include "iostream";
#include "functions.h";
enum class Color {white, black};
enum class Direction {positive, negative, constant};

class Figure
{
public:
	Figure
	(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix, std::vector<Figure*>& enemies);
	Color color;
	sf::Sprite body;
	
	std::vector<sf::Vector2f> moves{};
	bool playing = true;
	bool moved = false;
	bool pawn = false;
	bool tower = false;
	bool is_king = false;
	int val{};

	void display();
	virtual void calculate_moves(bool c = true);
	void dead();

protected:
	sf::Texture texture;
	sf::RenderWindow &window;
	std::array<std::array<int, 8>, 8>&matrix;
	std::string path = "textures/skoczek_czarny.png";
	Figure * king;
	std::vector<Figure*> &enemies;

	void read_textures();
	virtual bool check_pos(int x, int y, bool c = true);
	virtual bool check(int x, int y, bool c = true);
	void direction(int x, int y, Direction direction_x, Direction direction_y, bool c = true);
};



