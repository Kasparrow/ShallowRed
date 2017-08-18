#include "Functions.h"

char col_int_to_char(int x) {
	switch (x) {
	case 1:
		return 'a';
	case 2:
		return 'b';
	case 3:
		return 'c';
	case 4:
		return 'd';
	case 5:
		return 'e';
	case 6:
		return 'f';
	case 7:
		return 'g';
	case 8:
		return 'h';
	default:
		return '?';
	}

	return '?';
}

int col_char_to_int(char c) {
	switch (c) {
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	default:
		return 0;
	}

	return 0;
}

int direction(int src, int dest)
{
	int x_src = src / 8,
		y_src = src % 8,
		x_dest = dest / 8,
		y_dest = dest % 8;

	// - same line
	if (x_src == x_dest)
		return  0;

	// - same column
	else if (y_src == y_dest)
		return 1;

	// - top left to bottom right
	else if (x_src - x_dest == y_src - y_dest)
		return 2;

	// - top right to bottom left
	else if (abs(x_src - x_dest) == abs(y_src - y_dest))
		return 3;

	// - default
	return -1;
}
