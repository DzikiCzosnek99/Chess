#pragma once
#include "SFML/Graphics.hpp"
#include "knight.h"
#include "Tower.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "figure.h"
#include "iostream"
#include "vector"
#include "array"
#include "promotion.h"
#include "WinWindow.h"
#include "Menu.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:
	const unsigned int height = 800;
	const unsigned int width = 1100;
	sf::Image icon;
	bool play = true;

	WinWindow* winWindow;
	Menu * menu;
	Promotion* widget;

	sf::RenderWindow window;
	sf::Texture board_texture;
	sf::Sprite board;
	std::vector<sf::RectangleShape*> aPosiotions{};

	King *king_b;
	King *king_w;

	Knight *knight_b1;
	Knight *knight_b2;
	Knight *knight_w1;
	Knight *knight_w2;

	Tower *tower_b1;
	Tower *tower_b2;
	Tower *tower_w1;
	Tower *tower_w2;

	Bishop *bishop_b1;
	Bishop *bishop_b2;
	Bishop *bishop_w1;
	Bishop *bishop_w2;

	Pawn *pawn_b1;
	Pawn *pawn_b2;
	Pawn *pawn_b3;
	Pawn *pawn_b4;
	Pawn *pawn_b5;
	Pawn *pawn_b6;
	Pawn *pawn_b7;
	Pawn *pawn_b8;

	Pawn *pawn_w1;
	Pawn *pawn_w2;
	Pawn *pawn_w3;
	Pawn *pawn_w4;
	Pawn *pawn_w5;
	Pawn *pawn_w6;
	Pawn *pawn_w7;
	Pawn *pawn_w8;

	Queen *queen_b;
	Queen *queen_w;

	sf::RectangleShape alert;

	sf::Vector2f en_passants{ -100, -100 };
	Color player = Color::white;
	Figure* currFigure = nullptr;

	bool t1b_state = false;
	bool t2b_state = false;
	bool t1w_state = false;
	bool t2w_state = false;

	bool selected = false;
	bool need = false;

	std::vector<Figure*> figures_b{};
	std::vector<Figure*> figures_w{};
	std::vector<Figure*> figures = figures_w;
	std::vector<Figure*> enemies = figures_b;
	std::array<std::array<int,8>,8> matrix;

	void processEvents();
	void render();

	void fill_matrix();
	void display_positions();

	void dispay_figures();
	void delete_figures();

	void select_figure();
	void move_figure();

	void check();
	void promotion();
	void swap();
	void player_swap();

	void update_towers();
	void win();
	
	void create_widgets();
	void newGame();
	void pause();

	void check_reset();

	//undo
	std::vector<Figure*> figures_his{};
	std::vector<Figure*> deleted_figures_his{};
	std::vector<std::array<std::array<int, 8>, 8>> matrix_his{};
	std::vector<sf::Vector2f> moves_his{};
	std::vector<sf::Vector2f> deleted_moves_his{};
	std::vector<bool> states{};
	std::vector<bool> deleted_states{};
	std::vector<sf::Vector2f> en_passants_his{};
	std::vector<Figure*> new_figures{};
	int index = -1;

	std::vector<Figure*> towers{};
	std::vector<sf::Vector2f> towers_moves{};


	void save_position();
	void undo();
	void update_save_position();

	//redo
	std::vector<Figure*> figures_his2{};
	std::vector<Figure*> deleted_figures_his2{};
	std::vector<std::array<std::array<int, 8>, 8>> matrix_his2{};
	std::vector<sf::Vector2f> moves_his2{};
	std::vector<sf::Vector2f> deleted_moves_his2{};
	std::vector<sf::Vector2f> en_passants_his2{};

	std::vector<sf::Vector2f> towers_moves2{};

	std::vector<Figure*> kings{};
	std::vector<sf::Vector2f> king_moves{};

	int index2 = 0;

	void save_position2();
	void redo();

};



