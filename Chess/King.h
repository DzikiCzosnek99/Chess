#pragma once
#include "figure.h"
class King :
	public Figure
{
public:
	King(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix,
		std::vector<Figure*> &enemies, bool& t1_state, bool& t2_state);
	void calculate_moves(bool c = true) override;
private:
	std::vector<std::array<int, 2>> positions;
	bool check(int x, int y, bool c = true) override;
	bool& t1_state;
	bool& t2_state;
};

