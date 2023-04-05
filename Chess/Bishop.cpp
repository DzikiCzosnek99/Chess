#include "Bishop.h"
Bishop::Bishop(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	Figure* kingin, std::vector<Figure*>& enemies)
	: Figure(window, position, color, matrix,enemies)
{
	king = kingin;
	if (color == Color::black)
	{
		path = "textures/goniec_czarny.png";
	}

	else
	{
		path = "textures/goniec_bialy.png";
	}

	read_textures();
}

void Bishop::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x / 100;
	int y = body.getPosition().y / 100;

	direction(x, y, Direction::negative, Direction::positive, c);
	direction(x, y, Direction::negative, Direction::negative, c);
	direction(x, y, Direction::positive, Direction::positive, c);
	direction(x, y, Direction::positive, Direction::negative, c);
	
}




