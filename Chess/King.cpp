#include "King.h"
King::King(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
	std::vector<Figure*>& enemies, bool& t1_state, bool& t2_state)
	: Figure(window, position, color, matrix, enemies), t1_state(t1_state), t2_state(t2_state)
{
	is_king = true;
	if (color == Color::black)
	{
		path = "textures/krol_czarny.png";
	}

	else
	{
		path = "textures/krol_bialy.png";
	}

	read_textures();
}

bool King::check(int x, int y, bool c)
{
	if (c == false)
	{
		return true;
	}

	std::array<std::array<int, 8>, 8>copy = matrix;

	matrix[x][y] = val;
	matrix[int(body.getPosition().x / 100)][int(body.getPosition().y / 100)] = 0;

	for (auto fiq : enemies)
	{
		if (fiq->playing && (fiq->body.getPosition().x / 100 != x || fiq->body.getPosition().y / 100 != y))
		{
			fiq->calculate_moves(false);
			for (auto pos : fiq->moves)
			{
				if (pos.x == x * 100 && pos.y == y * 100)
				{
					matrix = copy;
					return false;
				}
			}
		}
	}
	matrix = copy;
	return true;
}
void King::calculate_moves(bool c)
{
	moves.clear();
	int x = body.getPosition().x / 100;
	int y = body.getPosition().y / 100;

	positions = {
		{x + 1, y + 1}, {x, y + 1}, {x - 1, y + 1},
		{x + 1, y - 1}, {x, y - 1}, {x - 1, y - 1},
		{x + 1, y}, {x - 1, y} };

	for (auto pos : positions)
	{
		check_pos(pos[0], pos[1], c);
	}

	if (moved == false)
	{
		int row{};
		if (color == Color::black) 
		{
			row = 0;
		}
		else 
		{
			row = 7;
		}

		if (t1_state == false)
		{
			if (matrix[1][row] == 0 & matrix[2][row] == 0 & matrix[3][row] == 0)
			{
				if (check(2, row, c) && check(3, row, c) && check(4, row, c))
				{
					moves.push_back(sf::Vector2f(0, row * 100));
				}
			}
		}
		if (t2_state == false)
		{
			if (matrix[6][row] == 0 & matrix[5][row] == 0)
			{
				if (check(6, row, c) && check(5, row, c) && check(4, row, c))
				{
					moves.push_back(sf::Vector2f(7 * 100, row*100));
				}
			}
		}
	}
		
}
	





