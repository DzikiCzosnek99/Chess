#pragma once
#include "figure.h"
class Queen :
	public Figure
{
public:
	Queen(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>,8>&matrix,
		Figure* kingin, std::vector<Figure*> &enemies);
	void calculate_moves(bool c = true) override;

};

