#pragma once
#include "figure.h"
#include "array"
class Knight :
	public Figure
{
public:
	Knight(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
		Figure* kingin, std::vector<Figure*> &enemies);
	void calculate_moves(bool c = true) override;
private:
	std::vector<std::array<int, 2>>positions;
};

