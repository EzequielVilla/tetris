#include <iostream>
#include "main.h"

/*
	Tiene que venir el vector de Position y cambiarle los valores dependiendo del objeto y el giro
*/

// Always start at top the init of the figure. 
// Square
//[0, 1, 1, 0]
//[0, 1, 1, 0]
//[0, 0, 0, 0]
//[0, 0, 0, 0]
// L
//[0, 0, 1, 1]     [0, 1, 0, 0]	[0, 0, 1, 0] [0, 1, 1, 1] 
//[0, 0, 1, 0]     [0, 1, 1, 1] [0, 0, 1, 0] [0, 0, 0, 1]
//[0, 0, 1, 0]	   [0, 0, 0, 0]	[0, 1, 1, 0] [0, 0, 0, 0]
//[0, 0, 0, 0]     [0, 0, 0, 0]	[0, 0, 0, 0] [0, 0, 0, 0]
// LITTLE T 
//[0, 1, 1, 1/
//[0, 0, 1, 0]
//[0, 0, 0, 0]
//[0, 0, 0, 0] 
// LITTLE I 
//[0, 0, 1, 0/
//[0, 0, 1, 0]
//[0, 0, 1, 0]
//[0, 0, 1, 0] 

enum RotateDirection {
	ROTATE_LEFT, ROTATE_RIGHT
};
enum FiguresType {
	SQUARE, ELE, LITTLE_T, BIGGER_I
};
//enum RotatePosition {
//	ONE, TWO, THREE, FOUR
//};

class Figure {
	const int CONTAINER = 4;
	bool** figure;
	FiguresType type;

	int position; // It must be btw 0 and 4;
public:
	Figure() {
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		int random_value = std::rand() % 4;
		//std::cout << random_value << std::endl;
		createContainer();
		switch (random_value)
		{
		case 0:
			createSquare();
			break;
		case 1:
			createT();
			break;
		case 2:
			createL();
			break;
		case 3:
			createI();
			break;
		default:
			std::cout << "Random number out of the expected" << std::endl;
			break;
		}
		this->position = 1;
		//createSquare(); 
		//createT(); 
		//createL(); 
		//createI();// OK

	};

	bool** getFigure() {
		return this->figure;
	}
	bool** rotate(FiguresType figure, RotateDirection rotate_direction) {
		
		// Devolver la forma que va a tener yyyy despues grid tiene que borrar y reemplazar la figura.
		switch (figure)
		{
		case SQUARE:
			return this->figure;
			break;
		case ELE:
			break;
		case LITTLE_T:
			break;
		case BIGGER_I:
			break;
		default:
			break;
		}


	}
private:
	void createContainer() {
		bool** arr = new bool* [CONTAINER];
		for (int i = 0; i < CONTAINER; ++i) {
			arr[i] = new bool[CONTAINER];
			for (int j = 0; j < CONTAINER; ++j) {
				arr[i][j] = 0;
			}
		}
		this->figure = arr;

	}
	void createSquare() {
		figure[0][1] = 1;
		figure[1][1] = 1;
		figure[0][2] = 1;
		figure[1][2] = 1;
		this->type = FiguresType::SQUARE;
	}
	void createT() {
		figure[0][1] = 1;
		figure[0][2] = 1;
		figure[0][3] = 1;
		figure[1][2] = 1;
		this->type = FiguresType::LITTLE_T;

	}
	void createL() {
		figure[0][2] = 1;
		figure[0][3] = 1;
		figure[1][2] = 1;
		figure[2][2] = 1;
		this->type = FiguresType::ELE;

	}
	void createI() {
		figure[0][2] = 1;
		figure[1][2] = 1;
		figure[2][2] = 1;
		figure[3][2] = 1;
		this->type = FiguresType::BIGGER_I;
	}

};


