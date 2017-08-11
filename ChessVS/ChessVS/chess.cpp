#include "chess.h"

#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>

Chess::Chess() {
	state = State();
	round = 0;
	whoseTurn = 0;
	lastMove = 0000;
}

Chess::Chess(std::array<std::array<int, 8>, 8> &st, int r, int wT, int lM) {
	state = State(st);
	round = r;
	whoseTurn = wT;
	lastMove = lM;
}


std::string Chess::stateToString(std::array<std::array<int, 8>, 8> &st) {
	std::string s = "";

	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			s += std::to_string(st[a][b]);
		}
	}

	return s;

}

std::tuple<int,int,int,int,std::string> Chess::nextTurn(int move) {

	std::tuple<int, int, int, int, std::string> ret;

	if (move != 0) {
		state.move(move / 100, move % 100);
		lastMove = move;
	}
	else {
		//Check whether CheckMate(1) or SteelMate 2
		int c;
		if (whoseTurn == 0)
			c = 1;
		else if (whoseTurn == 1)
			c = 0;
		int CMoSM = state.isCMoSM(c);
		if (CMoSM) {
			int winner = 0;
			if (CMoSM == 2) {
				winner = -1;
			}
			else {
				winner = whoseTurn;
			}

			ret = std::make_tuple(CMoSM, round, winner, lastMove, stateToString(state.state));

			return ret;
		}

		std::map<const int, std::vector<int>> pm;
		std::map<const int, std::vector<int>>::iterator it;

		pm = state.possibleMoves(whoseTurn);

		//check for CheckMatePossibility

		int nColor = 0;

		if (whoseTurn == 0)
			nColor = 1;
		int CMMove = 0000;
		
		for (std::pair<const int, std::vector<int>> a : pm) {
			for (int b : a.second) {
				std::array<std::array<int, 8>, 8> sstate = state.state;
				state.update(a.first, b);
				if (state.isCMoSM(nColor) == 1) {
					round += 1;

					ret = std::make_tuple(1, round, whoseTurn, a.first * 100 + b, stateToString(state.state));

					return ret;
				}
				state.state = sstate;
			}
		}
		//chose random move
		srand(time(NULL));

		it = pm.begin();

		std::advance(it, rand() % pm.size());

		int a = it->first;

		int r = rand() % pm[a].size() + 0;

		int b = pm[a][r];

		state.move(a, b);

		round += 1;

		int rWT = whoseTurn;

		if (whoseTurn == 0)
			whoseTurn = 1;
		else
			whoseTurn = 0;
		
		state.printState();

		std::cout << a * 100 + b << std::endl;

		ret = std::make_tuple(0, round, rWT, a * 100 + b, stateToString(state.state));

		return ret;
		
	}
	
}

std::tuple<int, int, int, std::string, std::vector<std::tuple<int,int,std::string>>> Chess::moveRecord() {
	if (round == 0) {

		int swt = whoseTurn; //saveWhoseTurn
		std::string sState = stateToString(state.state); //saveState

		std::tuple<int, int, int, int, std::string> nT = nextTurn();
		
		std::vector<std::tuple<int, int, std::string>> r;
		
		r.push_back(std::make_tuple(swt,std::get<3>(nT),sState));

		while (std::get<0>(nT) == 0) {
			swt = whoseTurn;
			sState = stateToString(state.state);

			nT = nextTurn();
			r.push_back(std::make_tuple(swt, std::get<3>(nT), sState));
		}

		int end = std::get<0>(nT);
		std::string finalState = stateToString(state.state);
		int winner = std::get<2>(nT);

		int rounds = std::get<1>(nT);

		return std::make_tuple(end, rounds, winner, finalState, r);

	}
}