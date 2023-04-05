#include "knight.h"

Knight::Knight(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	Figure* kingin, std::vector<Figure*>& enemies)
	: Figure(window, position, color, matrix, enemies)
{
	king = kingin;
	if (color == Color::black) 
	{
		path = "textures/skoczek_czarny.png";
	}

	else 
	{
		path = "textures/skoczek_bialy.png";
	}

	read_textures();
}

void Knight::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x/100;
	int y = body.getPosition().y/100;
	positions.clear();
	positions = {
		{x-1,y+2}, {x + 1,y + 2}, {x - 1,y - 2}, {x + 1,y - 2},
		{x - 2,y + 1}, {x + 2,y + 1}, {x - 2,y - 1}, {x + 2,y - 1}
	};

	for (auto position : positions)
	{
		check_pos(position[0], position[1], c);
	}
	
}




