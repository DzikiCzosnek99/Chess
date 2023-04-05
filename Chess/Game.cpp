#include "Game.h"
 
Game::Game() :
	window(sf::VideoMode(width, height), "Chess", sf::Style::Titlebar | sf::Style::Close), alert(sf::Vector2f(100.f, 100.f))
{
	icon.loadFromFile("textures/skoczek_czarny.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	create_widgets();
	board_texture.loadFromFile("textures/board.png");
	board.setTexture(board_texture);
	fill_matrix();
}

Game::~Game() 
{
	delete_figures();
}
void Game::processEvents() 
{
	sf::Event event;

	while (window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			check_reset();
			if (play) 
			{
				if (widget->show)
				{
					swap();
				}
				else if (selected == false)
				{
					select_figure();
				}
				else if (currFigure != nullptr)
				{
					move_figure();
				}
			}
			else 
			{
				pause();
			}
		}
	}
}

void Game::render() 
{
	window.clear();
	window.draw(board);
	display_positions();
	window.draw(alert);
	dispay_figures();
	widget->display();
	winWindow->display();
	menu->display();

	window.display();
}

void Game::run() 
{
	while (window.isOpen()) 
	{
		processEvents();
		render();
	}
}

void Game::fill_matrix() 
{
	for (int i = 0; i < 8; i++) 
	{
		for (int k = 0; k < 8; k++)
		{
			matrix[i][k] = 0;
		}
	}
	for (int i = 0; i < figures_b.size(); i++) 
	{
		int x = figures_b[i]->body.getPosition().x / 100;
		int y = figures_b[i]->body.getPosition().y / 100;
		matrix[x][y] = -1;

		x = figures_w[i]->body.getPosition().x / 100;
		y = figures_w[i]->body.getPosition().y / 100;
		matrix[x][y] = 1;

	}
}

void Game::display_positions() 
{
	if (currFigure != nullptr && need==false && aPosiotions.size() == 0)
	{
		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		rect->setFillColor(sf::Color(255, 255, 0, 150));
		rect->setPosition(currFigure->body.getPosition().x, currFigure->body.getPosition().y);
		aPosiotions.push_back(rect);
		for (auto pos : currFigure->moves)
		{
			sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
			if (pos == en_passants && currFigure->pawn)
			{
				rect->setFillColor(sf::Color(255, 0, 0, 240));
			}
			else if (matrix[pos.x / 100][pos.y / 100] != -currFigure->val)
			{
				rect->setFillColor(sf::Color(0, 0, 255, 150));
			}
			else
			{
				rect->setFillColor(sf::Color(255, 0, 0, 240));
			}

			rect->setPosition(pos);
			aPosiotions.push_back(rect);
		}
			
	}
		for (auto r : aPosiotions) 
		{
			window.draw(*r);
		}
	
}

void Game::dispay_figures() 
{
	for (int i = 0; i < figures_b.size(); i++) 
	{
		figures_b[i]->display();
	}
	for (int i = 0; i < figures_w.size(); i++)
	{
		figures_w[i]->display();
	}
}

void Game::delete_figures() 
{
	for (int i = 0; i < figures_b.size(); i++)
	{
		delete figures_b[i];
	}
	for (int i = 0; i < figures_w.size(); i++)
	{
		delete figures_w[i];
	}
	figures_b.clear();
	figures_w.clear();
	delete widget;
	delete winWindow;
	delete menu;
}

void Game::select_figure() 
{
	currFigure = nullptr;
	std::vector<Figure*> figures{};
	if (player == Color::white)
	{
		figures = figures_w;
	}
	else
	{
		figures = figures_b;
	}

	for (auto figure : figures)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = figure->body.getGlobalBounds();
		if (bounds.contains(mousePosition.x, mousePosition.y))
		{
			currFigure = figure;
			currFigure->calculate_moves();
			selected = true;
			break;
		}
	}
}

void Game::move_figure()
{
	selected = false;
	bool clicked = false;
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	sf::Vector2f newPosition(int(localPosition.x / 100) * 100.0f, int(localPosition.y / 100) * 100.0f);
	for (auto pos : currFigure->moves)
	{
		if (int(pos.x) == int(newPosition.x) && int(pos.y) == int(newPosition.y))
		{
			update_save_position();
			save_position();
			en_passants_his.push_back(en_passants);
			clicked = true;
			int x = currFigure->body.getPosition().x / 100;
			int y = currFigure->body.getPosition().y / 100;
			if (matrix[int(newPosition.x / 100)][int(newPosition.y / 100)] != 0)
			{
				for (auto figure : enemies)
				{
					int x = figure->body.getPosition().x / 100;
					int y = figure->body.getPosition().y / 100;

					if (x == int(newPosition.x / 100) && y == int(newPosition.y / 100))
					{
						deleted_figures_his.push_back(figure);
						deleted_moves_his.push_back(figure->body.getPosition());
						deleted_states.push_back(figure->moved);
						figure->dead();
						break;
					}
				}
			}
			else 
			{
				deleted_figures_his.push_back(nullptr);
				deleted_moves_his.push_back(sf::Vector2f(0, 0));
				deleted_states.push_back(false);
			}

			towers.push_back(nullptr);
			towers_moves.push_back(sf::Vector2f(-100, -100));
			towers_moves2.push_back(sf::Vector2f(-100, -100));

			kings.push_back(nullptr);
			king_moves.push_back(sf::Vector2f(-100, -100));

			matrix[x][y] = 0;
			matrix[int(newPosition.x / 100)][int(newPosition.y / 100)] = currFigure->val;
			currFigure->moved = true;
			currFigure->body.setPosition(newPosition);
			save_position2();
			update_towers();
			if (currFigure->is_king) 
			{
				if (abs(newPosition.x - x * 100) > 100) 
				{
					kings[index] = currFigure;
					deleted_figures_his.push_back(nullptr);
					deleted_moves_his.push_back(sf::Vector2f(0, 0));
					deleted_states.push_back(false);

					matrix[int(newPosition.x / 100)][int(newPosition.y / 100)] = 0;
					if (newPosition.x == 0.f) 
					{
						currFigure->body.setPosition(200, newPosition.y);
						king_moves[index] = (currFigure->body.getPosition());
						matrix[2][int(newPosition.y / 100)] = currFigure->val;
						for (auto fig : figures)
						{
							if (fig->tower)
							{
								if (fig->body.getPosition().x == 0.f)
								{
									towers[index] = (fig);
									towers_moves[index] = (fig->body.getPosition());

									fig->body.setPosition(300, newPosition.y);

									towers_moves2[index] = (fig->body.getPosition());
									matrix[3][int(newPosition.y / 100)] = currFigure->val;
									break;
								}
							}
						}	
					}
					else 
					{
						currFigure->body.setPosition(600, newPosition.y);
						king_moves[index] = (currFigure->body.getPosition());
						matrix[2][int(newPosition.y / 100)] = currFigure->val;
						for (auto fig : figures)
						{
							if (fig->tower)
							{
								if (fig->body.getPosition().x == 700.f)
								{
									towers[index] = (fig);
									towers_moves[index] = (fig->body.getPosition());

									fig->body.setPosition(500, newPosition.y);

									towers_moves2[index] = (fig->body.getPosition());
									matrix[5][int(newPosition.y / 100)] = currFigure->val;
									break;
								}
							}
						}
					}
				}
			}
			
			if (currFigure->pawn) 
			{
				if (abs(y - currFigure->body.getPosition().y / 100) > 1) 
				{
					en_passants = { x*100.f, currFigure->body.getPosition().y + 100*currFigure->val };
				}
				else if (currFigure->body.getPosition() == en_passants) 
				{
					for (auto figure : enemies)
					{
						if (figure->pawn)
						{
							int x = figure->body.getPosition().x / 100;
							int y = figure->body.getPosition().y / 100;

							if (x == int(newPosition.x / 100) && y == int(newPosition.y / 100) + currFigure->val)
							{
								deleted_figures_his[index] = figure;
								deleted_moves_his[index] = figure->body.getPosition();
								figure->dead();
								break;
							}
						}
					}
				}
				else
				{
					en_passants = { -100.f, -100.f };
				}
			}
			else
			{
				en_passants = { -100.f, -100.f };
			}
			en_passants_his2.push_back(en_passants);
			promotion();
			player_swap();
			check();
			win();
			
			break;
		}
	}
	currFigure->moves.clear();

	for (auto rect : aPosiotions)
	{
		delete rect;
	}
	aPosiotions.clear();
	if (need == false) 
	{
		currFigure = nullptr;
	}
	if (clicked == false) 
	{
		select_figure();
	}
}

void Game::check() 
{
	bool find = false;
	King* king;
	if (player == Color::white) 
	{
		king = king_w;
	}
	else
	{
		king = king_b;
	}

	for (auto fig : enemies) 
	{
		if (fig->playing) 
		{
			fig->calculate_moves(false);
	
			for (auto pos : fig->moves)
			{
				if (pos.x == king->body.getPosition().x && pos.y == king->body.getPosition().y)
				{
					find = true;
					break;
				}
			}
			if (find)
			{
				break;
			}
		}
		
	}
	if (find) 
	{
		alert.setPosition(king->body.getPosition().x, king->body.getPosition().y);
	}
	else
	{
		alert.setPosition(-100, -100);
	}
}

void::Game::promotion() 
{
	int val{};
	
	if (player == Color::black) 
	{
		val = 7;
	}
	else 
	{
		val = 0;
	}
	if (currFigure->pawn && int(currFigure->body.getPosition().y / 100) == val)
	{
		widget->show = true;
		widget->set(player);
		need = true;
	}
}

void Game::swap() 
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect bounds1 = widget->choice1.getGlobalBounds();
	sf::FloatRect bounds2 = widget->choice2.getGlobalBounds();
	sf::FloatRect bounds3 = widget->choice3.getGlobalBounds();
	sf::FloatRect bounds4 = widget->choice4.getGlobalBounds();
	bool clicked = false;
	
	if (bounds1.contains(mousePosition.x, mousePosition.y))
	{
		if (player == Color::black) 
		{
			figures_w.push_back(new Queen(window, currFigure->body.getPosition(), Color::white, matrix, king_w, figures_b));
		}
		else
		{
			figures_b.push_back(new Queen(window, currFigure->body.getPosition(), Color::black, matrix, king_b, figures_w));
		}
		widget->show = false;
		selected = false;
		need = false;
		clicked = true;
		
	}
	else if (bounds2.contains(mousePosition.x, mousePosition.y))
	{
		if (player == Color::black)
		{
			figures_w.push_back(new Tower(window, currFigure->body.getPosition(), Color::white, matrix, king_w, figures_b));
		}
		else
		{
			figures_b.push_back(new Tower(window, currFigure->body.getPosition(), Color::black, matrix, king_b, figures_w));
		}
		widget->show = false;
		selected = false;
		need = false;
		clicked = true;
	}
	else if (bounds3.contains(mousePosition.x, mousePosition.y))
	{
		if (player == Color::black)
		{
			figures_w.push_back(new Bishop(window, currFigure->body.getPosition(), Color::white, matrix, king_w, figures_b));
		}
		else
		{
			figures_b.push_back(new Bishop(window, currFigure->body.getPosition(), Color::black, matrix, king_b, figures_w));
		}
		widget->show = false;
		selected = false;
		need = false;
		clicked = true;
	}
	else if (bounds4.contains(mousePosition.x, mousePosition.y))
	{
		if (player == Color::black)
		{
			figures_w.push_back(new Knight(window, currFigure->body.getPosition(), Color::white, matrix, king_w, figures_b));
		}
		else
		{
			figures_b.push_back(new Knight(window, currFigure->body.getPosition(), Color::black, matrix, king_b, figures_w));
		}
		widget->show = false;
		selected = false;
		need = false;
		clicked = true;
	}
	if (clicked) 
	{
		int x = currFigure->body.getPosition().x / 100;
		int y = currFigure->body.getPosition().y / 100;
		currFigure->dead();
		matrix[x][y] = currFigure->val;
		deleted_figures_his2[index] = currFigure;
		currFigure = nullptr;
		if (player == Color::black)
		{
			new_figures[index] = (figures_w[figures_w.size() - 1]);
			deleted_moves_his2[index] = (figures_w[figures_w.size() - 1]->body.getPosition());
			enemies = figures_w;
		}
		else
		{
			new_figures[index] = (figures_b[figures_b.size() - 1]);
			deleted_moves_his2[index] = (figures_w[figures_w.size() - 1]->body.getPosition());
			enemies = figures_b;
		}
	}
}

void Game::player_swap() 
{
	menu->set();
	if (player == Color::white) 
	{
		figures = figures_b;
		enemies = figures_w;
		player = Color::black;
	}

	else
	{
		figures = figures_w;
		enemies = figures_b;
		player = Color::white;
	}
}

void Game::update_towers() 
{
	for (auto fig : figures_b)
	{
		if (fig->tower)
		{
			if (fig->body.getPosition().x == 0)
			{
				if (fig->moved)
				{
					t1b_state = true;
				}
				else
				{
					t1b_state = false;
				}
			}
			else
			{
				if (fig->moved)
				{
					t2b_state = true;
				}
				else
				{
					t2b_state = false;
				}
			}
		}
	}
	for (auto fig : figures_w)
	{
		if (fig->tower) 
		{
			if (fig->body.getPosition().x == 0)
			{
				if (fig->moved)
				{
					t1w_state = true;
				}
				else
				{
					t1w_state = false;
				}
			}
			else
			{
				if (fig->moved)
				{
					t2w_state = true;
				}
				else
				{
					t2w_state = false;
				}
			}
		}
	}			
}

void Game::win() 
{
	int n = 0;

	for (auto fig : figures) 
	{
		fig->calculate_moves();
		n = n + fig->moves.size();
		if (n > 0) 
		{
			break;
		}
	}

	if (n == 0) 
	{
		play = false;
		winWindow->show = true;
		winWindow->set(player);
	}
}

void Game::create_widgets() 
{
	winWindow = new WinWindow(window);
	menu = new Menu(window);
	alert.setFillColor(sf::Color(165, 42, 42, 255));
	alert.setPosition(-100, -100);

	king_b = new King(window, sf::Vector2f(400.0f, 0.0f), Color::black, matrix, figures_w, t1b_state, t2b_state);
	king_w = new King(window, sf::Vector2f(400.0f, 700.0f), Color::white, matrix, figures_b, t1w_state, t2w_state);

	knight_b1 = new Knight(window, sf::Vector2f(100.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	knight_b2 = new Knight(window, sf::Vector2f(600.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	knight_w1 = new Knight(window, sf::Vector2f(100.0f, 700.0f), Color::white, matrix, king_w, figures_b);
	knight_w2 = new Knight(window, sf::Vector2f(600.0f, 700.0f), Color::white, matrix, king_w, figures_b);

	tower_b1 = new Tower(window, sf::Vector2f(0.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	tower_b2 = new Tower(window, sf::Vector2f(700.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	tower_w1 = new Tower(window, sf::Vector2f(0.0f, 700.0f), Color::white, matrix, king_w, figures_b);
	tower_w2 = new Tower(window, sf::Vector2f(700.0f, 700.0f), Color::white, matrix, king_w, figures_b);

	bishop_b1 = new Bishop(window, sf::Vector2f(200.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	bishop_b2 = new Bishop(window, sf::Vector2f(500.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	bishop_w1 = new Bishop(window, sf::Vector2f(200.0f, 700.0f), Color::white, matrix, king_w, figures_b);
	bishop_w2 = new Bishop(window, sf::Vector2f(500.0f, 700.0f), Color::white, matrix, king_w, figures_b);

	pawn_b1 = new Pawn(window, sf::Vector2f(0.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b2 = new Pawn(window, sf::Vector2f(100.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b3 = new Pawn(window, sf::Vector2f(200.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b4 = new Pawn(window, sf::Vector2f(300.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b5 = new Pawn(window, sf::Vector2f(400.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b6 = new Pawn(window, sf::Vector2f(500.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b7 = new Pawn(window, sf::Vector2f(600.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);
	pawn_b8 = new Pawn(window, sf::Vector2f(700.0f, 100.0f), Color::black, matrix, king_b, figures_w, en_passants);

	pawn_w1 = new Pawn(window, sf::Vector2f(0.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w2 = new Pawn(window, sf::Vector2f(100.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w3 = new Pawn(window, sf::Vector2f(200.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w4 = new Pawn(window, sf::Vector2f(300.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w5 = new Pawn(window, sf::Vector2f(400.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w6 = new Pawn(window, sf::Vector2f(500.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w7 = new Pawn(window, sf::Vector2f(600.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);
	pawn_w8 = new Pawn(window, sf::Vector2f(700.0f, 600.0f), Color::white, matrix, king_w, figures_b, en_passants);

	queen_b = new Queen(window, sf::Vector2f(300.0f, 0.0f), Color::black, matrix, king_b, figures_w);
	queen_w = new Queen(window, sf::Vector2f(300.0f, 700.0f), Color::white, matrix, king_w, figures_b);

	widget = new Promotion(window, sf::Vector2f(325.f, 100.f));

	figures_b.push_back(knight_b1);
	figures_b.push_back(knight_b2);
	figures_b.push_back(tower_b1);
	figures_b.push_back(tower_b2);
	figures_b.push_back(bishop_b1);
	figures_b.push_back(bishop_b2);
	figures_b.push_back(pawn_b1);
	figures_b.push_back(pawn_b2);
	figures_b.push_back(pawn_b3);
	figures_b.push_back(pawn_b4);
	figures_b.push_back(pawn_b5);
	figures_b.push_back(pawn_b6);
	figures_b.push_back(pawn_b7);
	figures_b.push_back(pawn_b8);
	figures_b.push_back(queen_b);
	figures_b.push_back(king_b);


	figures_w.push_back(knight_w1);
	figures_w.push_back(knight_w2);
	figures_w.push_back(tower_w1);
	figures_w.push_back(tower_w2);
	figures_w.push_back(bishop_w1);
	figures_w.push_back(bishop_w2);
	figures_w.push_back(pawn_w1);
	figures_w.push_back(pawn_w2);
	figures_w.push_back(pawn_w3);
	figures_w.push_back(pawn_w4);
	figures_w.push_back(pawn_w5);
	figures_w.push_back(pawn_w6);
	figures_w.push_back(pawn_w7);
	figures_w.push_back(pawn_w8);
	figures_w.push_back(queen_w);
	figures_w.push_back(king_w);
}

void Game::newGame() 
{
	for (auto rect : aPosiotions)
	{
		delete rect;
	}

	widget->show = false;
	need = false;

	aPosiotions.clear();
	currFigure = nullptr;
	en_passants = { -100.f, -100.f };
	delete_figures();
	create_widgets();
	fill_matrix();
	player = Color::white;
	play = true;
	selected = false;

	index = -1;
	matrix_his.clear();
	figures_his.clear();
	moves_his.clear();
	deleted_figures_his.clear();
	deleted_moves_his.clear();
	states.clear();
	deleted_states.clear();
	en_passants_his.clear();
	new_figures.clear();
	towers.clear();
	towers_moves.clear();

	index2 = 0;
	matrix_his2.clear();
	figures_his2.clear();
	moves_his2.clear();
	deleted_moves_his2.clear();
	deleted_figures_his2.clear();
	en_passants_his2.clear();
	towers_moves2.clear();
	kings.clear();
	king_moves.clear();
}

void Game::pause()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = winWindow->button.getGlobalBounds();
	

	if (bounds.contains(mousePosition.x, mousePosition.y))
	{
		newGame();
	}
}

void Game::check_reset() 
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = menu->reset_button.getGlobalBounds();
	sf::FloatRect bounds2 = menu->undo_button.getGlobalBounds();
	sf::FloatRect bounds3 = menu->redo_button.getGlobalBounds();

	if (bounds.contains(mousePosition.x, mousePosition.y))
	{
		newGame();
	}
	if (play && widget->show==false) 
	{
		if (bounds2.contains(mousePosition.x, mousePosition.y))
		{
			undo();
		}

		if (bounds3.contains(mousePosition.x, mousePosition.y))
		{
			redo();
		}
	}
}

void Game::save_position() 
{
	figures_his.push_back(currFigure);
	matrix_his.push_back(matrix);
	moves_his.push_back(currFigure->body.getPosition());
	states.push_back(currFigure->moved);
	new_figures.push_back(nullptr);
	index++;
}
void Game::save_position2()
{
	figures_his2.push_back(currFigure);
	matrix_his2.push_back(matrix);
	moves_his2.push_back(currFigure->body.getPosition());
	deleted_moves_his2.push_back(sf::Vector2f(-100, -100));
	deleted_figures_his2.push_back(nullptr);
	index2++;
}

void Game::undo() 
{
	if (index >= 0) 
	{
		
		matrix = matrix_his[index];
		figures_his[index]->body.setPosition(moves_his[index]);
		figures_his[index]->playing = true;
		figures_his[index]->moved = states[index];
		en_passants = en_passants_his[index];
		if (deleted_figures_his[index] != nullptr) 
		{
			deleted_figures_his[index]->body.setPosition(deleted_moves_his[index]);
			deleted_figures_his[index]->playing = true;
			deleted_figures_his[index]->moved = deleted_states[index];
		}
		if (new_figures[index] != nullptr) 
		{
			new_figures[index]->dead();
		}
		if (towers[index] != nullptr)
		{
			towers[index]->body.setPosition(towers_moves[index]);
			towers[index]->moved = false;
		}
		update_towers();
		player_swap();
		check();
		index--;
		index2--;
	}
}

void Game::update_save_position() 
{
	int loop = matrix_his.size() - index - 1;
	for (int i = 0; i < loop; i++)
	{
		matrix_his.pop_back();
		figures_his.pop_back();
		moves_his.pop_back();
		deleted_figures_his.pop_back();
		deleted_moves_his.pop_back();
		states.pop_back();
		deleted_states.pop_back();
		en_passants_his.pop_back();
		new_figures.pop_back();
		towers.pop_back();
		towers_moves.pop_back();

		matrix_his2.pop_back();
		figures_his2.pop_back();
		moves_his2.pop_back();
		deleted_moves_his2.pop_back();
		deleted_figures_his2.pop_back();
		en_passants_his2.pop_back();
		towers_moves2.pop_back();
		kings.pop_back();
		king_moves.pop_back();
	}
}

void Game::redo()
{
	if (index2 < moves_his2.size())
	{
		matrix = matrix_his2[index2];
		figures_his2[index2]->body.setPosition(moves_his2[index2]);
		figures_his2[index2]->playing = true;
		figures_his2[index2]->moved = true;
		en_passants = en_passants_his2[index2];
		if (deleted_figures_his[index2] != nullptr)
		{
			deleted_figures_his[index2]->dead();
		}
		if (new_figures[index2] != nullptr)
		{
			new_figures[index2]->body.setPosition(deleted_moves_his2[index2]);
			new_figures[index2]->playing = true;
		}
		if (deleted_figures_his2[index2] != nullptr)
		{
			deleted_figures_his2[index2]->dead();
		}
		if (towers[index2] != nullptr)
		{
			towers[index2]->body.setPosition(towers_moves2[index2]);
			towers[index2]->moved = true;
		}
		if (kings[index2] != nullptr) 
		{
			kings[index2]->body.setPosition(king_moves[index2]);
			kings[index2]->moved = true;
		}
		update_towers();
		player_swap();
		check();
		index2++;
		index++;
	}
}