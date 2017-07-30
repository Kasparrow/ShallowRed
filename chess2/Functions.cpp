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
