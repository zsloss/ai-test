#include <iostream>
#include <string>
#include "world.h"

int main(int argc, char* argv[]) {

    std::cout << "\n** AI TEST **\n" << std::endl;

    World w;

    w.add_people(5);

    for (int i = 1; i <= 10; i++) {
        std::cout << std::endl << "Cycle " << i << ":\n" << std::endl;
        w.update();
    }   
}
