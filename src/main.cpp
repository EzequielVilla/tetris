#include <iostream>
#include <vector>
#include <ostream>
#include "figures.cpp"
#include "main.h"
//#include "./game.cpp"
// x=0 its roof y x = mx_size its floor.
struct Position {
	int x;
	int y;
};
struct Collision {
	bool border;
	bool bottom;
	bool figure;
};
enum Inputs {
	DOWN, LEFT, RIGHT, ROTATE
};


struct CheckRows {
	std::vector<int> rows;
	int starting_row;
};

class Grid {
	std::vector <std::vector<bool>> myGrid;
	int mx_size;
	int my_size;
	std::vector<Position> positionsVectorFigure;
	FiguresType m_figure_type;

public:
	Grid(int x_size, int y_size) {
		std::vector<std::vector<bool> >v(x_size, std::vector<bool>(y_size, false));
		mx_size = x_size;
		my_size = y_size;
		myGrid = v;
	}
	void PrintInTerminal() {
		for (int i = 0; i < mx_size; i++) {
			std::cout << "	";
			for (int j = 0; j < my_size; j++) {
				std::cout << myGrid[i][j] << " ";
			}
			std::cout << " Row: " << i << " " << std::endl;
		}
	}
	void insertFigure(bool** figure) {
		// Clean the positions of the previous figure. 
		this->positionsVectorFigure.clear();
		const int MAX_FIGURE_SIZE = 4;
		int half_y_size = my_size / 2 - 2;
		int x_count = 0;
		// save the positions in a vector for next movement.
		for (int i = 0; i < MAX_FIGURE_SIZE; i++) {
			int y_init = 0;
			int count = 0;
			for (int j = 0; j < MAX_FIGURE_SIZE; j++) {
				if (figure[i][j] == 1) {
					int column_position = half_y_size + j;
					myGrid[i][column_position] = 1;
					Position p = { i, column_position };
					this->positionsVectorFigure.push_back(p);
				}
			}
		}
		//this->m_figure_type = figure.
	}
	Collision moveFigure(Inputs letter) {
		Collision collision = collisionChecker(letter);
		if (collision.bottom || collision.figure) {
			//only true bottom
			return collision;
		}
		if (!collision.border) {
			DeletePrePosition();
			setNewPositions(letter);
			setNewPositionsInGrid();
			//only true border
			return collision;
			;
		}
		//// All in false
		return collision;
	}
	void postProcess() {
		CheckRows checked_rows = this->checkRows();
		if (checked_rows.rows.size() != 0) {
			int rows_deleted = checked_rows.rows.size();
			this->deleteCompletedRows(checked_rows.rows);
			this->moveOnesAfterDelete(checked_rows);

		}

	}
private:
	Collision collisionChecker(Inputs letter) {
		Collision collision{};
		collision.bottom = false;
		collision.border = false;
		collision.figure = false;
		switch (letter)
		{
		case DOWN:
			for (Position position : positionsVectorFigure) {
				int next_x_position = position.x++;
				int next_y_position = position.y;
				if (position.x == mx_size) {
					std::cout << "Bottom " << std::endl;
					collision.bottom = true;
					break;
				}
				//Implementar esta logica para los casos de los costados y rotacion
				bool isHimself = getItsThisFigure(position);
				if (!isHimself) {
					bool next_value = myGrid[position.x][position.y];
					if (next_value) {
						collision.figure = true;
						break;
					}
				}
			}
			break;
		case LEFT:
			for (Position position : positionsVectorFigure) {
				int next_x_pos = position.x++;
				int next_y_post = position.y--;

				if (position.x == mx_size) {
					collision.bottom = true;
					break;
				}
				else if (position.x > mx_size || position.y < 0) {
					collision.border = true;
					break;
				}
				bool isHimself = getItsThisFigure(position);
				if (!isHimself) {
					bool next_value = myGrid[position.x][position.y];
					if (next_value) {
						collision.border = true;
						break;
					}
				}
			}
			break;
		case RIGHT:
			for (Position position : positionsVectorFigure) {
				position.x++;
				position.y++;
				if (position.x == mx_size) {
					std::cout << "Bottom " << std::endl;
					collision.bottom = true;
					break;
				}
				else if (position.x > mx_size || position.y > my_size - 1) {
					std::cout << "BORDER " << std::endl;
					collision.border = true;
					break;
				}
				/*bool border_figure = this->getCollisionBorderFigure(position);
				collision.border = border_figure;*/
				bool isHimself = getItsThisFigure(position);
				if (!isHimself) {
					bool next_value = myGrid[position.x][position.y];
					if (next_value) {
						collision.border = true;
						break;
					}
				}
			}
			break;
		case ROTATE:
			// Enviar a la clase figura como son los cambios de posiciones dependiendo de la figura que envio, es decir, cuanto en X Y tiene que cambiar, que posiciones pasar a 0 y cuales a 1 de 
			// los que le envio. Pero para eso tengo que saber el tipo y no tengo ese dato. Al menos que el figure tenga incluido no solo un bool** sino que ademas tenga un enum
			// del tipo figura para que puedas saber si es un cuadrado, L , T , I. 
			// Cada cambio deberia ser algo ya guardado, como un array, porque puede girar a la izq o a la derecha. Entonces pasaria de rotation[0] a rotation[1] o rotation[3] (de 0 tiene que pasar a 3)
			// Y ademas tiene que saber, en ese enum, no solo el tipo, sino que tambien debe conservarse el valor de que en posicion de rotacion esta. Entonces debe guardarse en una variable de la clase
			// En realidad la instancia misma podria tener un getter setter y no devolver un struct con tanta info. sino que sea Figure f -> f.rotate() y la misma figura, instancia,
			// va a tener todos los datos guardado dentro.
			std::cout << "NOT IMPLEMENTED YET " << std::endl;
			break;
		default:
			break;
		}
		return collision;
	}
	//bool getCollisionBorderFigure(Position position) {
	//	bool isHimself = getItsThisFigure(position);
	//	if (!isHimself) {
	//		bool next_value_is_border = myGrid[position.x][position.y];
	//		return next_value_is_border;
	//	}
	//}
	bool getItsThisFigure(Position new_position) {
		for (Position position : positionsVectorFigure) {
			int new_position_x = new_position.x;
			int new_position_y = new_position.y;
			int storage_position_x = position.x;
			int storage_position_y = position.y;

			if (new_position_x == storage_position_x && new_position_y == storage_position_y) {
				return true;
			}
		}
		return false;
	}
	void DeletePrePosition() {
		for (Position& position : positionsVectorFigure) {
			myGrid[position.x][position.y] = 0;
		}
	}
	void setNewPositions(Inputs letter) {
		switch (letter)
		{
		case DOWN:
			for (Position& position : positionsVectorFigure) {
				position.x++;
			}
			break;
		case LEFT:
			for (Position& position : positionsVectorFigure) {
				position.x++;
				position.y--;
			}
			break;
		case RIGHT:
			for (Position& position : positionsVectorFigure) {
				position.x++;
				position.y++;
			}
			break;
		case ROTATE:
			std::cout << "NOT IMPLEMENTED YET " << std::endl;
			break;
		default:
			break;
		}
	}
	void setNewPositionsInGrid() {
		for (Position& position : positionsVectorFigure) {
			myGrid[position.x][position.y] = 1;
		}
	}
	CheckRows checkRows() {
		CheckRows info{};
		std::vector<int> rows;
		int starting_row = -1; // Save in which row i must start looking
		for (int i = 0; i < mx_size; i++) {
			int count = 0;
			// Count how many TRUE's are in the row
			for (int j = 0; j < my_size; j++) {
				if (myGrid[i][j]) {
					count++;
				}
			}
			if (count == my_size) {
				rows.push_back(i);
				if (starting_row < 0) {
					starting_row = i;
				}
			}
		}
		info.rows = rows;
		info.starting_row = starting_row;
		return info;
	}
	void deleteCompletedRows(std::vector<int> rows) {
		int size = rows.size();
		for (int i = 0; i < size; i++) {
			int actual_row = rows[i];
			for (int j = 0; j < my_size; j++) {
				myGrid[actual_row][j] = 0;
			}
		}

	}
	void moveOnesAfterDelete(CheckRows data) {
		int rows_size = data.rows.size(); // Rows deleted.
		int starting_row = data.starting_row;
		int countCerosInY = 0;

		for (int i = starting_row; i > 0; i--) {
			for (int j = 0; j < my_size; j++) {
				// Search how many rows up i have to look the value
				int row_on = i - rows_size;
				// If i'm outside the grid
				if (row_on < 0) {
					myGrid[i][j] = false;
				}
				else {
					// This is a count to check if all the row is equal to 0 and force a break to not consume or read all the rows.
					if (myGrid[row_on][j] == 0) {
						countCerosInY++;
					}
					// Catch the value in the row upper the deleted;
					int val = myGrid[row_on][j];
					// Replace the value in the deleted or replaced rows. At the begining its the deleted and after that is all the replaced
					myGrid[i][j] = val;
				}

			}
			if (countCerosInY == my_size) {
				break;
			}
			countCerosInY = 0;
		}

	}

};


Inputs ConvertToEnum(char letter) {
	if (letter == *"a") {
		return Inputs::LEFT;
	}
	else if (letter == *"s") {
		return Inputs::DOWN;
	}
	else if (letter == *"d") {
		return Inputs::RIGHT;
	}
	else if (letter == *"e") {
		return Inputs::ROTATE;
	}
	else {
		std::cout << "Options are A, S , D , E" << std::endl;
	}
}
Inputs getMovement() {
	char letter;
	std::cout << "Choose the movement: ";
	std::cin >> letter;
	char lowerLetter = tolower(letter);
	Inputs movement = ConvertToEnum(lowerLetter);
	return movement;
}

int main() {
	Grid g(10, 8);

	Figure f;
	bool** figure = f.getFigure();
	bool gameOn = true;
	Collision collision{};
	g.insertFigure(figure);
	while (gameOn) {
		g.PrintInTerminal();

		Inputs movement = getMovement();
		Collision inGameCollision = g.moveFigure(movement);

		if (inGameCollision.bottom || inGameCollision.figure) {
			g.postProcess();
			// insert new figure. 
			Figure f2;
			bool** next_figure = f2.getFigure(); // TODO implent to show the next figure in the terminal . 
			g.insertFigure(next_figure);
		}
	}
}

