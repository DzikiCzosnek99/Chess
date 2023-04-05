#include "figure.h"

Figure::Figure(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix, std::vector<Figure*>& enemies)
	:window(window), color(color), matrix(matrix), enemies(enemies)
{
	body.setPosition(position);
	if (color == Color::white) 
	{
		val = 1;
	}
	else 
	{
		val = -1;
	}
}

void Figure::read_textures() 
{
	texture.loadFromFile(path);
	body.setTexture(texture);
}

void Figure::display()
{
	window.draw(body);
}

void Figure::calculate_moves(bool c)
{

};

void::Figure::dead() 
{
	matrix[body.getPosition().x / 100][body.getPosition().y / 100] = 0;
	body.setPosition(-1000, -1000);
	playing = false;
}

bool Figure::check_pos(int x, int y, bool c)
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		if (matrix[x][y] == 0)
		{
			if (check(x, y, c))
			{
				moves.push_back(sf::Vector2f(x * 100.0f, y * 100.0f));
			}
			return true;
		}
		else if (matrix[x][y] == -val)
		{
			if (check(x, y, c))
			{
				moves.push_back(sf::Vector2f(x * 100.0f, y * 100.0f));
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Figure::check(int x, int y, bool c)
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
				if (pos.x == king->body.getPosition().x && pos.y == king->body.getPosition().y)
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

void Figure::direction(int x, int y, Direction direction_x, Direction direction_y, bool c) 
{
	bool cont = true;
	while (cont)
	{
		if (direction_x == Direction::negative) 
		{
			x = x - 1;
		}
		else if (direction_x == Direction::positive) 
		{
			x = x + 1;
		}
		if (direction_y == Direction::negative)
		{
			y = y - 1;
		}
		else if (direction_y == Direction::positive)
		{
			y = y + 1;
		}
		cont = check_pos(x, y, c);
	}
}