#pragma once

#ifndef __STATE_H_INCLUDED__
#define __STATE_H_INCLUDED__

static const int EMPTY_FIELD[8][8] = { { 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } ,{ 0,0,0,0,0,0,0,0 } };
static const int STARTING_POSITION[8][8] = { { 2,3,4,5,6,4,3,2 },{ 1,1,1,1,1,1,1,1 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ -1,-1,-1,-1,-1,-1,-1,-1 },{ -2,-3,-4,-5,-6,-4,-3,-2 } };

static const int CASTLING = -1;
static const int wRight = -2;
static const int wLeft = -3;
static const int bRight = -4;
static const int bLeft = -5;


#include <vector>
#include <array>
#include <map>


class State
{
public:

	std::array<std::array<int,8>,8> state;

	bool whiteRook1Moved;
	bool whiteRook2Moved;
	bool whiteKingMoved;

	bool blackRook1Moved;
	bool blackRook2Moved;
	bool blackKingMoved;

	State(std::array<std::array<int,8>,8> &st);
	State();

	void printState();
	
	void update(int pFrom, int pTo);
	void move(int pFrom, int pTo);

	int getKing(int color);
	bool onlyKings();
	
	bool isCheck(int color);
	int isCMoSM(int color);

	std::map<const int, std::vector<int>> possibleMoves(int color);
	void insertValue(std::map<const int, std::vector<int>> & pm, std::map<const int, std::vector<int>>::iterator & it, int x, int v);
	void delImpossibleMoves(std::map<const int, std::vector<int>> & pm, std::map<const int, std::vector<int>>::iterator & it, int color);
	void addPossibleCastling(std::map<const int, std::vector<int>> &pm, std::map<const int, std::vector<int>>::iterator & it, int color);

	

};

#endif