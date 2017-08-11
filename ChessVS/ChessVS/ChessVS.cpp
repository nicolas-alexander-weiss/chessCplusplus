// ChessCONSOLE.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


//POSSIBLE IMPROVEMENTS:
//
// - using color: (1/-1) instead of 0/1; would make extra mtp-variable obsolete

//#include "stdafx.h"
#include <iostream>
#include "chess.h"
#include <fstream>

using namespace std;

//BLACK TO WHITE STATE
string btws(string s) {
	int pos = s.length() - 1;
	char t = 'q';
	string c = "";
	string newState = "";

	for (int a = 0; a < 8; a++) {
		c = "";
		for (int b = 0; b < 8; b++) {
			t = s[pos];
			if (t != '0') {
				c = t + c;
				if (s[pos - 1] == '-') {
					pos -= 1;
				}
				else {
					c = '-' + c;
				}
			}
			else {
				c = '0' + c;
			}
		}
		newState += c;
	}
	return newState;
}


//BLACK TO WHITE MOVE
int btwm(int m) {
	if (m < 0) {
		return m+2;
	}
	else {
		int a = m / 1000;
		int b = (m % 1000) / 100;
		int c = (m % 100) / 10;
		int d = (m % 10);

		return ((7 - a) * 1000 + b * 100 + (7 - c) * 10 + d);
	}
}

void saveToDB(tuple<int, int, int, string, vector<tuple<int, int, string>>> x) {
	if (get<0>(x) == 1) {
		int rounds = get<1>(x);

		if (get<2>(x) == 0) {

		}

	}
	else
		cout << "NO USUAL ENDING!!" << endl;
}


void saveToTXT(Chess &ch) {
	tuple<int, int, int, string, vector<tuple<int, int, string>>> x = ch.moveRecord();
	string s;
	tuple<int, int, string > t;
	if (get<0>(x) == 1) {

		ofstream temp("temp.txt");
		if (temp.is_open()) {
			if (get<2>(x) == 0) {

				vector<tuple<int, int, string>> r = get<4>(x);

				for (int i = r.size() - 1; i > -1; i -= 2) {

					t = r[i];

					s = get<2>(t);

					temp << s.c_str() << " " << get<1>(t) << "1" << "\n" ;
				}
				for (int i = r.size() - 2; i > -1; i -= 2) {

					t = r[i];

					s = get<2>(t);

					temp << btws(s).c_str() << " " << btwm(get<1>(t)) << "-1" << "\n";
				}
			}
			temp.close();
		}
	}
	
}


int main()
{

	array<array<int, 8>, 8> st = { 2,0,0,3,4,0,0,0,0,0,0,0,6,0,0,0,1,0,0,4,-1,1,0,1,0,-1,1,0,0,0,1,0,0,0,0,-5,0,0,0,0,0,1,0,0,0,0,-3,0,0,0,0,-6,-4,-1,-1,-2,-4,0,0,0,-3,0,-2,0 };
	Chess ch = Chess(st);

	cout << "start" << endl;

	cout << ch.state.isCheck(0);

	/*tuple<int, int, int, string, vector<tuple<int, int, string>>> x = ch.moveRecord();
	cout << "end: " << get<0>(x) << endl;
	cout << "rounds: " << get<1>(x) << endl;
	cout << "winner: " << get<2>(x) << endl;*/

	ch.state.printState();
	//ch.nextTurn();
	int k = ch.state.getKing(1);
	ch.state.state[k / 10][k % 10];
	ch.state.printState();
	/*
		map<const int, vector<int>> pm = ch.state.possibleMoves(1);

	for (pair<const int, vector<int>> i : pm) {
		cout << i.first << endl;
		for (int x : i.second) {
			cout << "	" << x << endl;
		}
	}*/
	
	//ch.nextTurn();


	cout << "end" << endl;


	int y;
	cin >> y;

    return 0;
}

