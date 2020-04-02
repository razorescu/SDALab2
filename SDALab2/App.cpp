#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testAllExtended();
    testReunion();
    std::cout << "Finished IL Tests!" << std::endl;
    system("pause");
}