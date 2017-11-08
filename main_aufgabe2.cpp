#include <iostream>
#include <string>
#include "CAbase.h"


int main() {
    CAbase test(30, 30);
    test.aliveCell(1,1);
    test.aliveCell(0,1);
    test.aliveCell(1,2);
    test.evolveallCells();
    test.setCell(10,10);
    test.setField(10,10);

    system("pause");

    return 0;

}
