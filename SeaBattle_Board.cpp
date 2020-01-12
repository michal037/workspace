/* Michal Kozakiewicz 10.01.2020 */

#include <iostream> /* bad_alloc, cout, endl */
#include <ctime> /* time */
#include <cstdlib> /* srand, rand */

using namespace std;

typedef enum {
	SEABATTLE_BOARD_STATE_EMPTY,
	SEABATTLE_BOARD_STATE_SHIP,
	SEABATTLE_BOARD_STATE_DESTROYED
} SeaBattle_Board_State;

class SeaBattle_Board {
protected:
	SeaBattle_Board_State **board;
	const unsigned char board_row;
	const unsigned char board_column;

public:
	const unsigned char get_board_row() const noexcept {
		return this->board_row;
	}

	const unsigned char get_board_column() const noexcept {
		return this->board_column;
	}

	void clear_board() noexcept {
		for(unsigned char r = 0; r < this->get_board_row(); r++) {
			for(unsigned char c = 0; c < this->get_board_column(); c++) {
				this->board[r][c] = SEABATTLE_BOARD_STATE_EMPTY;
			}
		}
	}

	SeaBattle_Board(const unsigned char row, const unsigned char column):
		board_row(row), board_column(column) {
			/* disallow dimension of 0 */
			if(this->get_board_row() == 0) {
				throw "SeaBattle_Board: SeaBattle_Board(): Board row is 0!";
			}

			if(this->get_board_column() == 0) {
				throw "SeaBattle_Board: SeaBattle_Board(): Board column is 0!";
			}

			/* allocate memory */
			try {
				this->board = new SeaBattle_Board_State*[this->get_board_row()];
				for(unsigned char r = 0; r < this->get_board_row(); r++) {
					this->board[r] = new SeaBattle_Board_State[this->get_board_column()];
				}
			} catch(bad_alloc& e) {
				throw "SeaBattle_Board: SeaBattle_Board(): Bad allocation!";
			}

			/* set default state */
			this->clear_board();
	}

	virtual ~SeaBattle_Board() noexcept {
		/* free memory */
		for(unsigned char r = 0; r < this->get_board_row(); r++) {
			delete[] this->board[r];
		}
		delete[] this->board;
	}

	const SeaBattle_Board_State get(const unsigned char row, const unsigned char column) const {
		/* check input ranges */
		if(row >= this->get_board_row()) {
			throw "SeaBattle_Board: get(): Row range exceeded!";
		}

		if(column >= this->get_board_column()) {
			throw "SeaBattle_Board: get(): Column range exceeded!";
		}

		return this->board[row][column];
	}

	SeaBattle_Board& set(const unsigned char row, const unsigned char column, const SeaBattle_Board_State value) {
		/* check input ranges */
		if(row >= this->get_board_row()) {
			throw "SeaBattle_Board: set(): Row range exceeded!";
		}

		if(column >= this->get_board_column()) {
			throw "SeaBattle_Board: set(): Column range exceeded!";
		}

		this->board[row][column] = value;

		return *this;
	}

	void print() const noexcept {
		bool use_coordinates = false;

		/* use coordinates if board size is less than equal 26x26 */
		if((this->get_board_row() <= 26) && (this->get_board_column() <= 26)) {
			use_coordinates = true;
		}

		/* top coordinate */
		if(use_coordinates == true) {
			cout << "  ";
			for(unsigned char c = 0; c < this->get_board_column(); c++) {
				cout << " " << (char)('A' + c);
			}
			cout << endl;
		}

		/* print board */
		for(unsigned char r = 0; r < this->get_board_row(); r++) {
			/* left coordinate */
			if(use_coordinates == true) {
				if(r <= 9) {
					cout << " ";
				}

				cout << (unsigned int) r << " ";
			}

			/* board */
			for(unsigned char c = 0; c < this->get_board_column(); c++) {
				if(c > 0) {
					cout << " ";
				}

				/* select the appropriate symbol for the enum state */
				switch(this->board[r][c]) {
					case SEABATTLE_BOARD_STATE_EMPTY:
						cout << "*";
						break;

					case SEABATTLE_BOARD_STATE_SHIP:
						cout << "O";
						break;

					case SEABATTLE_BOARD_STATE_DESTROYED:
						cout << "X";
						break;

					default:
						cout << "*";
						break;
				}
			}

			cout << endl;
		}
	}
};

int main() {
	/* initialize pseudo random seed */
	srand(time(NULL));

	try {
		SeaBattle_Board board(26, 26);

		/* set random data in board */
		for(unsigned char r = 0; r < board.get_board_row(); r++) {
			for(unsigned char c = 0; c < board.get_board_column(); c++) {
				board.set(r, c, (SeaBattle_Board_State)(rand() % 3));
			}
		}

		board.print();
	} catch(const char *text) {
		cerr << text << endl;
	} catch(...) {
		cerr << "Unrecognized error!" << endl;
	}

	return 0;
}

/*
   A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 0 O X X X O * * X O O X X X X X * * * X O * X * * X X
 1 O O * * O X O X O X * * X * O O * * O O X * * X * X
 2 X * * X * * * X X O O X X X O X * X X * O X O * X O
 3 O O O O X * O O * * X * O X O * X X O X X X O * O *
 4 X O * * * X O X * * O X * * * X X X O X X X O * * *
 5 * X X O O O X * O O * * * * O O * O * O * X * X O X
 6 * O X O O O X * * X * O O X * * X X X X O O X X * *
 7 O O X X O X X * * O X O O X * * * * * O X * * O O *
 8 O O X X X X * * O * X X X * O X X X X X * O * * X O
 9 O * X X * X X X O X O O X O X * * * X O * O O X X X
10 X * X * * * * * O X * O X O X O X X O X X O O X * *
11 X X O X X * X X X O X * O * O O O O O X X O X * * O
12 X * * O O * O X O X X O * O X X X O O * X O X X * O
13 * * X O * O X * O * X O * * O * X X * O X O X * * X
14 X X O X * * X X X O X O * X X X X * O O O O X X * *
15 X O * O X * O O X * * X * * X * * X X X * * * * X O
16 * X O * X * X O O * * * O * O X X * O * * O X O O X
17 O O O * * O X O O O X O X * X X O * * O X * X X X X
18 * * O O X O * O O * * * O * * X * * O X X O O * * X
19 * O O O * X X * O X X X * O * * O O O X O X O O X X
20 O X X * * X O O O O O X O O X X * O O O * O * O X O
21 * * * O * X X * * * X O X * X * X * * * X * * * * O
22 X * * X O O * O * X * O O X * * X X O X * * X O O X
23 * * O X * * * * * X O * X * * O X * * X X O X * * X
24 * X * X * O X O X O * X X X O * O X X X * X * O O O
25 X X * X X X * * O X X X X X * X X * * X X X * O O O
*/
