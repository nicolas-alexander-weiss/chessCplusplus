#include "state.h"
#include <iostream>




//Constructors

State::State(std::array<std::array<int,8>,8> &st) {

	whiteRook1Moved = false;
	whiteRook2Moved = false;
	whiteKingMoved = false;

	blackRook1Moved = false;
	blackRook2Moved = false;
	blackKingMoved = false;

	state = st;
}

State::State() {
	whiteRook1Moved = false;
	whiteRook2Moved = false;
	whiteKingMoved = false;

	blackRook1Moved = false;
	blackRook2Moved = false;
	blackKingMoved = false;

	state = {2,3,4,5,6,4,3,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, -1,-1,-1,-1,-1,-1,-1,-1 ,-2,-3,-4,-5,-6,-4,-3,-2 };
}

//OTHER MEMBER FUNCTIONS

void State::printState() {
	std::cout << std::endl;

	for (int a = 7; a >= 0; a--) {
		for (int b = 0; b < 8; b++) {
			int c = state[a][b];

			if (c >= 0)
				std::cout << " ";

			std::cout << c << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void State::update(int pFrom, int pTo){
	if (pFrom == -1) {
		if (pTo == -2) {
			int m[4] = { 04,06,07,05 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -3) {
			int m[4] = { 04,02,00,03 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -4) {
			int m[4] = { 74,76,77,75 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -5) {
			int m[4] = { 74,72,70,73 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
	}
	else {
		int c = state[pFrom / 10][pFrom % 10];

		state[pTo / 10][pTo % 10] = c;
		state[pFrom / 10][pFrom % 10] = 0;

		if (c == 1 && pTo/10 == 7) {
			state[pTo / 10][pTo % 10] = 5;
		}
		if (c == -1 && pTo/10 == 0) {
			state[pTo / 10][pTo % 10] = -5;
		}

	}
}
void State::move(int pFrom, int pTo){
	if (pFrom == -1) {
		if (pTo == -2) {
			int m[4] = { 04,06,07,05 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -3) {
			int m[4] = { 04,02,00,03 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -4) {
			int m[4] = { 74,76,77,75 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
		if (pTo == -5) {
			int m[4] = { 74,72,70,73 };

			update(m[0], m[1]);
			update(m[2], m[3]);
		}
	}
	else {
		int c1 = state[pFrom/10][pFrom%10];
		int c2 = state[pTo/10][pTo%10];

		if (abs(c1) == 2 || abs(c2) == 2) {
			if ((pFrom / 10 == 0 && pFrom % 10 == 0) || (pTo / 10 == 0 && pTo % 10 == 0)) {
				whiteRook1Moved = true;
			}
			if ((pFrom / 10 == 0 && pFrom % 10 == 7) || (pTo / 10 == 0 && pTo % 10 == 7)) {
				whiteRook2Moved = true;
			}
			if ((pFrom / 10 == 7 && pFrom % 10 == 0) || (pTo / 10 == 7 && pTo % 10 == 0)) {
				blackRook1Moved = true;
			}
			if ((pFrom / 10 == 7 && pFrom % 10 == 7) || (pTo / 10 == 7 && pTo % 10 == 7)) {
				blackRook2Moved = true;
			}
		}
		if (abs(c1) == 6 || abs(c2) == 6) {
			if ((pFrom / 10 == 0 && pFrom % 10 == 4) || (pTo / 10 == 0 && pTo % 10 == 4)) {
				whiteKingMoved = true;
			}
			if ((pFrom / 10 == 7 && pFrom % 10 == 4) || (pTo / 10 == 7 && pTo % 10 == 4)) {
				blackKingMoved = true;
			}
		}

		state[pTo / 10][pTo % 10] = c1;
		state[pFrom / 10][pFrom % 10] = 0;

		if (c1 == 1 && pTo/10 == 7) {
			state[pTo / 10][pTo % 10] = 5;
		}
		if (c1 == -1 && pTo/10 == 0) {
			state[pTo / 10][pTo % 10] = -5;
		}

	}
}

int State::getKing(int color) {
	int p = 0;

	int k;

	if (color == 0)
		k = 6;
	else if (color == 1)
		k = -6;

	for (int a = 0; a <= 7; a++) {
		for (int b = 0; b <= 7; b++) {
			if (state[a][b] == k) {
				p += 10 * a;
				p += b;
			}
		}
	}

	

	return p;
}
bool State::onlyKings() {
	int c;
	int counter = 0;
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			c = state[a][b];
			if (c != 6 && c != -6) {
				if (c != 0)
					return false;
			}
			counter += 1;
		}
	}
	return true;
}

bool State::isCheck(int color) {
	int mtp = 1;
	if (color == 0) {
		mtp = 1;
	}
	else if (color == 1) {
		mtp = -1;
	}

	int p = getKing(color);

	std::array<int, 2> k = { p / 10 , p % 10 };

	
	int cField = 0;

	//check diagonally
	//up/right

	for (int i = 1; i < 8; i++) {

		if ((k[0] + i) > 7 || (k[1] + i) > 7) {
			break;
		}
		else {
			cField = state[k[0] + i][k[1] + i];
			if (i == 1 && cField == -6 * mtp)
				return true;
			if (color == 0 && i == 1 && cField == -1)
				return true;
			if (color == 0 && (cField > 0 || cField == -1 || cField == -2 || cField == -3 || cField == -6))
				break;
			if (color == 1 && (cField < 0 || cField == 1 || cField == 2 || cField == 3 || cField == 6))
				break;
			if (cField == -4 * mtp || cField == -5 * mtp)
				return true;
		}
	}

	//up/left

	for (int i = 1; i < 8; i++) {

		if ((k[0] + i) > 7 || (k[1] - i) < 0) {
			break;
		}
		else {
			cField = state[k[0] + i][k[1] - i];
			if (i == 1 && cField == -6 * mtp)
				return true;
			if (color == 0 && i == 1 && cField == -1)
				return true;
			if (color == 0 && (cField > 0 || cField == -1 || cField == -2 || cField == -3 || cField == -6))
				break;
			if (color == 1 && (cField < 0 || cField == 1 || cField == 2 || cField == 3 || cField == 6))
				break;
			if (cField == -4 * mtp || cField == -5 * mtp)
				return true;
		}
	}

	//down/right

	for (int i = 1; i < 8; i++) {

		if ((k[0] - i) < 0 || (k[1] + i) > 7) {
			break;
		}
		else {
			cField = state[k[0] - i][k[1] + i];
			if (i == 1 && cField == -6 * mtp)
				return true;
			if (color == 1 && i == 1 && cField == 1)
				return true;
			if (color == 0 && (cField > 0 || cField == -1 || cField == -2 || cField == -3 || cField == -6))
				break;
			if (color == 1 && (cField < 0 || cField == 1 || cField == 2 || cField == 3 || cField == 6))
				break;
			if (cField == -4 * mtp || cField == -5 * mtp)
				return true;
		}
	}

	//down/left

	for (int i = 1; i < 8; i++) {

		if ((k[0] - i) < 0 || (k[1] - i) < 0) {
			break;
		}
		else {
			cField = state[k[0] - i][k[1] - i];
			if (i == 1 && cField == -6 * mtp)
				return true;
			if (color == 1 && i == 1 && cField == 1)
				return true;
			if (color == 0 && (cField > 0 || cField == -1 || cField == -2 || cField == -3 || cField == -6))
				break;
			if (color == 1 && (cField < 0 || cField == 1 || cField == 2 || cField == 3 || cField == 6))
				break;
			if (cField == -4 * mtp || cField == -5 * mtp)
				return true;
		}
	}

	//check vertically

	//up

	for (int i = 1; i < 8; i++) {
		if (k[0] + i > 7) {
			break;
		}
		else {
			cField = state[k[0] + i][k[1]];
			if (i == 1 && cField == -6 * mtp)
				return true;
			if (color == 0 && (cField > 0 || cField == -1 || cField == -3 || cField == -4 || cField == -6))
				break;
			if (color == 1 && (cField > 0 || cField == 1 || cField == 3 || cField == 4 || cField == 6))
				break;
			if (cField == -2 * mtp || cField == -5 * mtp)
				return true;
		}
	}

	//down

for (int i = 1; i < 8; i++) {
	if (k[0] - i < 0) {
		break;
	}
	else {
		cField = state[k[0] - i][k[1]];
		if (i == 1 && cField == -6 * mtp)
			return true;
		if (color == 0 && (cField > 0 || cField == -1 || cField == -3 || cField == -4 || cField == -6))
			break;
		if (color == 1 && (cField > 0 || cField == 1 || cField == 3 || cField == 4 || cField == 6))
			break;
		if (cField == -2 * mtp || cField == -5 * mtp)
			return true;
	}
}

//check horizontally

//right

for (int i = 1; i < 8; i++) {
	if (k[1] + i > 7) {
		break;
	}
	else {
		cField = state[k[0]][k[1] + i];
		if (i == 1 && cField == -6 * mtp)
			return true;
		if (color == 0 && (cField > 0 || cField == -1 || cField == -3 || cField == -4 || cField == -6))
			break;
		if (color == 1 && (cField < 0 || cField == 1 || cField == 3 || cField == 4 || cField == 6))
			break;
		if (cField == -2 * mtp || cField == -5 * mtp)
			return true;
	}
}

//left

for (int i = 1; i < 8; i++) {
	if (k[1] - i < 0) {
		break;
	}
	else {
		cField = state[k[0]][k[1] - i];
		if (i == 1 && cField == -6 * mtp)
			return true;
		if (color == 0 && (cField > 0 || cField == -1 || cField == -3 || cField == -4 || cField == -6))
			break;
		if (color == 1 && (cField < 0 || cField == 1 || cField == 3 || cField == 4 || cField == 6))
			break;
		if (cField == -2 * mtp || cField == -5 * mtp)
			return true;
	}
}

//check for knights

for (int a = 1; a < 3; a++) {
	int b;
	if (a == 1)
		b = 2;
	else if (a == 2)
		b = 1;

	if ((k[0] + a) <= 7 && (k[1] - b) >= 0) {
		if (state[k[0] + a][k[1] - b] == -3 * mtp)
			return true;
	}
	if ((k[0] + a) <= 7 && (k[1] + b) <= 7) {
		if (state[k[0] + a][k[1] + b] == -3 * mtp)
			return true;
	}
	if ((k[0] - a) >= 0 && (k[1] - b) >= 0) {
		if (state[k[0] - a][k[1] - b] == -3 * mtp)
			return true;
	}
	if ((k[0] - a) >= 0 && (k[1] + b) <= 7) {
		if (state[k[0] - a][k[1] + b] == -3 * mtp)
			return true;
	}
}
return false;
}
int State::isCMoSM(int color) {
	std::map<const int, std::vector<int>> pM = possibleMoves(color);
	bool iC = isCheck(color);

	if (pM.size() == 0 && iC == true)
		return 1;
	if ((pM.size() == 0 && iC == false) || onlyKings() == true)
		return 2;
	else
		return 0;

}

void State::insertValue(std::map<const int, std::vector<int>> & pM, std::map<const int, std::vector<int>>::iterator & it, int x, int y) {
	it = pM.find(x);

	if (it == pM.end()) {
		pM.insert(pM.begin(), std::pair<const int, std::vector<int>>(x, std::vector<int>{ {y}}));
		//cout << x << " " << y << endl;

	}
	else {

		if (find(pM[x].begin(), pM[x].end(), y) == pM[x].end()) {
			pM[x].push_back(y);
			//cout << x << " " << y << endl;
		}
	}
}


void State::delImpossibleMoves(std::map<const int, std::vector<int>> & pM, std::map<const int, std::vector<int>>::iterator & it, int color) {
	if (pM.empty()) {

	}
	else {
		std::vector<int> delM = {};
		for (it = pM.begin(); it != pM.end(); it++) {
			//pair<const int,  vector<int>> i : pM) {
			
			std::vector<int> delV = {};

			for (int a = (it->second).size() - 1; a >= 0; a--) {
				std::array<std::array < int, 8>, 8> sstate = state;
				update(it->first, (it->second)[a]);

				if (isCheck(color) == true) {

					delV.push_back(a);

					if ((it->second).size() == delV.size()) {
						delM.push_back(it->first);
					}
				}
				int q = 0;
				state = sstate;

			}
			
			std::sort(delV.begin(), delV.end());

			for (int i1 = delV.size(); i1 >= 1; i1--) {
				(it->second).erase((it->second).begin() + delV[i1 - 1]);
			}
		}


		for (int x : delM) {
			pM.erase(pM.find(x));
		}
	}
}
void State::addPossibleCastling(std::map<const int, std::vector<int>> &pm, std::map<const int, std::vector<int>>::iterator & it, int color) {

	

	if (color == 0) {
		if (whiteKingMoved == false) {
			std::array<int, 8> row = state[0];
			if (whiteRook1Moved == false) {
				bool wayFree = true;
				bool noCheck = true;
				for (int i = 3; i > 0; i--) {
					if (row[i] != 0) {
						wayFree = false;
						break;
					}
				}
				if (wayFree == true) {
					if (isCheck(1) == false) {
						for (int i = 3; i > 0; i--) {
							for (int i = 3; i > 1; i--) {
								state[0][i] = 6;
								if (isCheck(0) == true) {
									noCheck = false;
									state[0][i] = 0;
									break;
								}
								state[0][i] = 0;
							}
						}
					}
					else {
						noCheck = false;
					}
					if (noCheck == true) {
						insertValue(pm, it, -1, -3);
					}
				}
			}
			if (whiteRook2Moved == false) {

				bool wayFree = true;
				for (int i = 5; i < 7; i++) {
					if (row[i] != 0) {
						wayFree = false;
					}
				}
				if (wayFree == true) {
					bool noCheck = true;
					if (isCheck(0) == false) {
						for (int i = 5; i < 7; i++) {
							state[0][i] = 6;
							if (isCheck(0) == true) {
								noCheck = false;
								state[0][i] = 0;
								break;
							}
							state[0][i] = 0;
						}
					}
					else {
						noCheck = false;
					}
					if (noCheck == true) {
						insertValue(pm, it, -1, -2);
					}
				}
			}
		}
	}

	if (color == 1) {
		if (blackKingMoved == false) {
			std::array<int, 8> &row = state[7];
			if (blackRook1Moved == false) {
				
				bool wayFree = true;
				for (int i = 5; i < 7; i++) {
					if (row[i] != 0) {
						wayFree = false;
					}
				}
				if (wayFree == true) {
					bool noCheck = true;
					if (isCheck(1) == false) {
						for (int i = 5; i < 7; i++) {
							state[7][i] = -6;
							if (isCheck(1) == true) {
								noCheck = false;
								state[7][i] = 0;
								break;
							}
							state[7][i] = 0;
						}
					}
					else {
						noCheck = false;
					}
					if (noCheck == true) {
						insertValue(pm, it, -1, -5);
					}
				}
			}
			if (blackRook2Moved == false) {
				bool wayFree = true;
				for (int i = 5; i < 7; i++) {
					if (row[i] != 0) {
						wayFree = false;
					}
				}
				if (wayFree == true) {
					bool noCheck = true;
					if (isCheck(1) == false) {
						for (int i = 5; i < 7; i++) {
							state[7][i] = -6;
							if (isCheck(1) == true) {
								noCheck = false;
								state[7][i] = 0;
								break;
							}
							state[7][i] = 0;
						}
					}
					else {
						noCheck = false;
					}
					if (noCheck == true) {
						insertValue(pm, it, -1, -4);
					}
				}
			}
		}
	}
}

std::map<const int, std::vector<int>> State::possibleMoves(int color) {
	std::map<const int, std::vector<int>> pM;
	std::map<const int, std::vector<int>>::iterator it;

	int cPiece = 0;
	int cField = 0;

	//WHITE

	if (color == 0) {
		for (int a = 0; a < 8; a++) {
			for (int b = 0; b < 8; b++) {
				cPiece = state[a][b];
				if (cPiece > 0) {

					//WHITE_PAWN

					if (cPiece == 1) {
						if (a == 1) {
							for (int i = 0; i < 2; i++) {
								cField = state[a + 1 + i][b];

								if (cField == 0) {

									insertValue(pM, it, a * 10 + b, 10 * (a + 1 + i) + b);

								}
								else {
									break;
								}
							}
						}
						if (a != 7) {
							if (state[a + 1][b] == 0) {

								insertValue(pM, it, 10 * a + b, 10 * (a + 1) + b);

							}
							if (b != 0) {
								if (state[a + 1][b - 1] < 0) {

									insertValue(pM, it, 10 * a + b, 10 * (a + 1) + b - 1);

								}
							}
							if (b != 7) {
								if (state[a + 1][b + 1] < 0) {

									insertValue(pM, it, 10 * a + b, 10 * (a + 1) + b + 1);

								}
							}
						}
					}

					//WHITE_ROOK

					else if (cPiece == 2) {
						//vertically
						for (int i = a + 1; i < 8; i++) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField > 0)
								break;
						}
						for (int i = a - 1; i > -1; i--) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField > 0)
								break;
						}
						//horizontally
						for (int i = b + 1; i < 8; i++) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField > 0)
								break;
						}
						for (int i = b - 1; i > -1; i--) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField > 0)
								break;
						}
					}

					//WHITE_KNIGHT

					else if (cPiece == 3) {
						if (a + 1 < 8) {
							if (b - 2 > -1) {
								cField = state[a + 1][b - 2];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b - 2);
							}
							if (b + 2 < 8) {
								cField = state[a + 1][b + 2];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b + 2);
							}
						}
						if (a + 2 < 8) {
							if (b - 1 > -1) {
								cField = state[a + 2][b - 1];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 2) + b - 1);
							}
							if (b + 1 < 8) {
								cField = state[a + 2][b + 1];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 2) + b + 1);
							}
						}
						if (a - 1 > -1) {
							if (b - 2 > -1) {
								cField = state[a - 1][b - 2];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b - 2);
							}
							if (b + 2 < 8) {
								cField = state[a + 1][b + 2];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b + 2);
							}
						}
						if (a - 2 > -1) {
							if (b - 1 > -1) {
								cField = state[a - 2][b - 1];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 2) + b - 1);
							}
							if (b + 1 < 8) {
								cField = state[a - 2][b + 1];
								if (cField <= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 2) + b + 1);
							}
						}
					}

					//WHITE_BISHOP

					else if (cPiece == 4) {
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b + i > 7)
								break;
							else {
								cField = state[a + i][b + i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b - i < 0)
								break;
							else {
								cField = state[a + i][b - i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b + i > 7)
								break;
							else {
								cField = state[a - i][b + i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b - i < 0)
								break;
							else {
								cField = state[a - i][b - i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
									break;
								}
							}
						}
					}

					//WHITE_QUEEN
					else if (cPiece == 5) {
						//COMBINATION OF ROOK AND BISHOP

						//ROOK_PART

						//vertically
						for (int i = a + 1; i < 8; i++) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField > 0)
								break;
						}
						for (int i = a - 1; i > -1; i--) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField > 0)
								break;
						}
						//horizontally
						for (int i = b + 1; i < 8; i++) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField > 0)
								break;
						}
						for (int i = b - 1; i > -1; i--) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField < 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField > 0)
								break;
						}

						//BISHOP_PART

						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b + i > 7)
								break;
							else {
								cField = state[a + i][b + i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b - i < 0)
								break;
							else {
								cField = state[a + i][b - i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b + i > 7)
								break;
							else {
								cField = state[a - i][b + i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b - i < 0)
								break;
							else {
								cField = state[a - i][b - i];
								if (cField > 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
								}
								else if (cField < 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
									break;
								}
							}
						}
					}

					//WHITE_KING

					else if (cPiece == 6) {
						if (a + 1 < 8) {
							if (state[a + 1][b] <= 0) {
								insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b);
							}
							if (b + 1 < 8) {
								if (state[a + 1][b + 1] <= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b + 1);
								}
							}
							if (b - 1 > -1) {
								if (state[a + 1][b - 1] <= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b - 1);
								}
							}
						}
						if (a - 1 > -1) {
							if (state[a - 1][b] <= 0) {
								insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b);
							}
							if (b + 1 < 8) {
								if (state[a - 1][b + 1] <= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b + 1);
								}
							}
							if (b - 1 > -1) {
								if (state[a - 1][b - 1] <= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b - 1);
								}
							}
						}
						if (b + 1 < 8) {
							if (state[a][b + 1] <= 0)
								insertValue(pM, it, a * 10 + b, 10 * a + b + 1);
						}
						if (b - 1 > -1) {
							if (state[a][b - 1] <= 0)
								insertValue(pM, it, a * 10 + b, 10 * a + b - 1);
						}
					}
				}
			}
		}
	}


	//BLACK 

	else if (color == 1) {
		for (int a = 0; a < 8; a++) {
			for (int b = 0; b < 8; b++) {
				cPiece = state[a][b];

				if (cPiece < 0) {

					//BLACK_PAWN

					if (cPiece == -1) {
						if (a == 6) {
							for (int i = 1; i <= 2; i++) {
								cField = state[a - i][b];

								if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b);
								}
								else {
									break;
								}
							}
						}
						if (a != 7) {
							if (state[a - 1][b] == 0) {
								insertValue(pM, it, 10 * a + b, 10 * (a - 1) + b);
							}
							if (b != 0) {
								if (state[a - 1][b - 1] > 0) {
									insertValue(pM, it, 10 * a + b, 10 * (a - 1) + b - 1);
								}
							}
							if (b != 7) {
								if (state[a - 1][b + 1] > 0) {
									insertValue(pM, it, 10 * a + b, 10 * (a - 1) + b + 1);
								}
							}
						}
					}

					//BLACK_ROOK

					else if (cPiece == -2) {
						//vertically
						for (int i = a + 1; i < 8; i++) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField < 0)
								break;
						}
						for (int i = a - 1; i > -1; i--) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField < 0)
								break;
						}
						//horizontally
						for (int i = b + 1; i < 8; i++) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField < 0)
								break;
						}
						for (int i = b - 1; i > -1; i--) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField < 0)
								break;
						}
					}

					//BLACK_KNIGHT

					else if (cPiece == -3) {
						if (a + 1 < 8) {
							if (b - 2 > -1) {
								cField = state[a + 1][b - 2];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b - 2);
							}
							if (b + 2 < 8) {
								cField = state[a + 1][b + 2];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b + 2);
							}
						}
						if (a + 2 < 8) {
							if (b - 1 > -1) {
								cField = state[a + 2][b - 1];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 2) + b - 1);
							}
							if (b + 1 < 8) {
								cField = state[a + 2][b + 1];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a + 2) + b + 1);
							}
						}
						if (a - 1 > -1) {
							if (b - 2 > -1) {
								cField = state[a - 1][b - 2];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b - 2);
							}
							if (b + 2 < 8) {
								cField = state[a - 1][b + 2];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b + 2);
							}
						}
						if (a - 2 > -1) {
							if (b - 1 > -1) {
								cField = state[a - 2][b - 1];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 2) + b - 1);
							}
							if (b + 1 < 8) {
								cField = state[a - 2][b + 1];
								if (cField >= 0)
									insertValue(pM, it, a * 10 + b, 10 * (a - 2) + b + 1);
							}
						}
					}

					//BLACK_BISHOP

					else if (cPiece == -4) {
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b + i > 7)
								break;
							else {
								cField = state[a + i][b + i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b - i < 0)
								break;
							else {
								cField = state[a + i][b - i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b + i > 7)
								break;
							else {
								cField = state[a - i][b + i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b - i < 0)
								break;
							else {
								cField = state[a - i][b - i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
									break;
								}
							}
						}
					}

					//BLACK_QUEEN
					else if (cPiece == -5) {
						//COMBINATION OF ROOK AND BISHOP

						//ROOK_PART

						//vertically
						for (int i = a + 1; i < 8; i++) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField < 0)
								break;
						}
						for (int i = a - 1; i > -1; i--) {
							cField = state[i][b];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * i + b);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * i + b);
								break;
							}
							else if (cField < 0)
								break;
						}
						//horizontally
						for (int i = b + 1; i < 8; i++) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField < 0)
								break;
						}
						for (int i = b - 1; i > -1; i--) {
							cField = state[a][i];
							if (cField == 0)
								insertValue(pM, it, 10 * a + b, 10 * a + i);
							else if (cField > 0) {
								insertValue(pM, it, 10 * a + b, 10 * a + i);
								break;
							}
							else if (cField < 0)
								break;
						}

						//BISHOP_PART

						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b + i > 7)
								break;
							else {
								cField = state[a + i][b + i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a + i > 7 || b - i < 0)
								break;
							else {
								cField = state[a + i][b - i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + i) + b - i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b + i > 7)
								break;
							else {
								cField = state[a - i][b + i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b + i);
									break;
								}
							}
						}
						for (int i = 1; i < 8; i++) {
							if (a - i < 0 || b - i < 0)
								break;
							else {
								cField = state[a - i][b - i];
								if (cField < 0)
									break;
								else if (cField == 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
								}
								else if (cField > 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - i) + b - i);
									break;
								}
							}
						}

					}

					//BLACK_KING

					else if (cPiece == -6) {
						if (a + 1 < 8) {
							if (state[a + 1][b] >= 0) {
								insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b);
							}
							if (b + 1 < 8) {
								if (state[a + 1][b + 1] >= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b + 1);
								}
							}
							if (b - 1 > -1) {
								if (state[a + 1][b - 1] >= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a + 1) + b - 1);
								}
							}
						}
						if (a - 1 > -1) {
							if (state[a - 1][b] >= 0) {
								insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b);
							}
							if (b + 1 < 8) {
								if (state[a - 1][b + 1] >= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b + 1);
								}
							}
							if (b - 1 > -1) {
								if (state[a - 1][b - 1] >= 0) {
									insertValue(pM, it, a * 10 + b, 10 * (a - 1) + b - 1);
								}
							}
						}
						if (b + 1 < 8) {
							if (state[a][b + 1] >= 0)
								insertValue(pM, it, a * 10 + b, 10 * a + b + 1);
						}
						if (b - 1 > -1) {
							if (state[a][b - 1] >= 0)
								insertValue(pM, it, a * 10 + b, 10 * a + b - 1);
						}
					}
				}

			}
		}
	}
	else {
		std::cout << "ERROR: Color not specified WHITE (0) OR BLACK(1)" << std::endl;
	}

	delImpossibleMoves(pM, it, color);
	addPossibleCastling(pM, it, color);

	return pM;
}
