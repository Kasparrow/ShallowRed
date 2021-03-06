#include <iostream>
#include <cstdio>

#include "../include/board/Board.h"
#include "../include/utils/Functions.h"

using namespace std;

int main(int argc, char** argv) 
{
    Board b;

    b.print();
    const int res = b.game();
    print_result(res);

    std::cout << "Press any key to exit program\n";
    getchar();

    return 0;
}
