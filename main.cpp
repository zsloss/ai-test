#include <iostream>
#include <string>
#include <vector>
#include "library.h"
#include "Person.h"

int main(int argc, char* argv[]) {
    std::cout << "** AI TEST **" << std::endl << std::endl;
    Person p1 = Person();
    for (int i = 0; i < 100; i++)
        p1.update();
    Person p2 = Person();
    p1.inform(p2, "enters");
    std::vector<Person> people = {Person(), Person()};
}
