#pragma once

#ifndef __CHESS_H_INCLUDED__
#define __CHESS_H_INCLUDED__

#include "state.h"



class Chess {
public:
	State state;

	int round;
	int whoseTurn;
	int lastMove;


	Chess();
	Chess(std::array<std::array<int, 8>, 8> &st, int r = 0, int wT = 0, int lM = 0000);

	std::tuple<int,int,int,int,std::string> nextTurn(int move = 0);
	std::tuple<int, int, int, std::string, std::vector<std::tuple<int, int, std::string>>>moveRecord();
	
	std::string stateToString(std::array<std::array<int, 8>, 8> &st);

	

};

#endif