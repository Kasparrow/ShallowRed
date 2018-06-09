#include<iostream>
#include <stdio.h>
#include "Board.h"

using namespace std;

int main(int argc, char** argv) {
	Board b;
	int res;

	b.print();
	res = b.game();

	switch (res) {
	case Board::BLACK_WIN:
		cout << "0 - 1\n";
		break;
	case Board::WHITE_WIN:
		cout << "1 - 0\n";
		break;
	case Board::DRAW:
		cout << "0,5 - 0,5\n";
	default:
		break;
	}

	getchar();

	return 0;
}