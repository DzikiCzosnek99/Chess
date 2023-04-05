#include "Queen.h"
Queen::Queen(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	Figure* kingin, std::vector<Figure*>& enemies)
	: Figure(window, position, color, matrix, enemies)
{
	king = kingin;
	if (color == Color::black)
	{
		path = "textures/hetman_czarny.png";
	}

	else
	{
		path = "textures/hetman_bialy.png";
	}

	read_textures();
}

void Queen::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x / 100;
	int y = body.getPosition().y / 100;

	direction(x, y, Direction::negative, Direction::positive, c);
	direction(x, y, Direction::negative, Direction::negative, c);
	direction(x, y, Direction::positive, Direction::positive, c);
	direction(x, y, Direction::positive, Direction::negative, c);

	direction(x, y, Direction::negative, Direction::constant, c);
	direction(x, y, Direction::constant, Direction::negative, c);
	direction(x, y, Direction::positive, Direction::constant, c);
	direction(x, y, Direction::constant, Direction::positive, c);
}
	
