#include "Tower.h"
Tower::Tower(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	Figure* kingin, std::vector<Figure*>& enemies)
	: Figure(window, position, color, matrix, enemies)
{
	king = kingin;
	tower = true;
	if (color == Color::black)
	{
		path = "textures/wieza_czarna.png";
	}

	else
	{
		path = "textures/wieza_biala.png";
	}

	read_textures();
}

void Tower::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x / 100;
	int y = body.getPosition().y / 100;

	direction(x, y, Direction::negative, Direction::constant, c);
	direction(x, y, Direction::constant, Direction::negative, c);
	direction(x, y, Direction::positive, Direction::constant, c);
	direction(x, y, Direction::constant, Direction::positive, c);
}

