#include<iostream>
#include <stdio.h>

#include "Board.h"
#include "Functions.h"

using namespace std;

int main(int argc, char** argv) 
{
    Board b;
    int res;

    b.print();
    res = b.game();
    print_result(res);

    std::cout << "Press any key to exit program\n";
    getchar();

    return 0;
}