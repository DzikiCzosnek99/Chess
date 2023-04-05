#include "Pawn.h"
Pawn::Pawn(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	Figure* kinginin, std::vector<Figure*>& enemies, sf::Vector2f& en_passants)
	: Figure(window, position, color, matrix, enemies), en_passants(en_passants)
{
	king = kinginin;
	pawn = true;
	if (color == Color::black)
	{
		path = "textures/pion_czarny.png";
	}

	else
	{
		path = "textures/pion_bialy.png";
	}

	read_textures();
}

void Pawn::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x / 100;
	int y = body.getPosition().y / 100;
	std::vector<std::array<int, 2>>positions{
		{x, y - val}, {x, y - 2 * val}, {x + 1 ,y - val}, {x - 1,y - val}};

	for (auto pos : positions) 
	{
		check_pawn(pos[0], pos[1], c);
	}
}

void Pawn::check_pawn(int x, int y, bool c) 
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		if (x == body.getPosition().x/100)
		{
			if (matrix[x][y] == 0)
			{
				if (abs(y - body.getPosition().y/100) == 1 && check(x, y, c))
				{
					moves.push_back(sf::Vector2f(x * 100, y * 100));
				}
				else if (moved == false && matrix[x][y+val] == 0 && check(x, y, c))
				{
					moves.push_back(sf::Vector2f(x * 100, y * 100));
				}
			}
		}
		else if (matrix[x][y] == -val && check(x, y, c))
		{
			moves.push_back(sf::Vector2f(x * 100, y * 100));
		}
		else if (en_passants.x / 100 == x && en_passants.y / 100 == y && check(x, y, c)) 
		{
			moves.push_back(sf::Vector2f(x * 100, y * 100));
		}
	}
};
