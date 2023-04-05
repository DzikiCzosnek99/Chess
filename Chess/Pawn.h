#pragma once
#include "figure.h"
class Pawn :
	public Figure
{
public:
	Pawn(sf::RenderWindow &window, sf::Vector2f position, Color color, std::array<std::array<int, 8>, 8>&matrix
	,Figure* kingin, std::vector<Figure*> &enemies,sf::Vector2f& en_passants);

	void calculate_moves(bool c = true) override;
	sf::Vector2f& en_passants;
private:
	void check_pawn(int x, int y, bool c = true);
};

