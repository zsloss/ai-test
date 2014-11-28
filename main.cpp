#include <iostream>
#include <string>
#include <vector>
#include "library.h"
#include "person.h"
#include "environment.h"

class Person;
class Environment;

int main(int argc, char* argv[]) {
    std::cout << "\n** AI TEST **\n" << std::endl;
    Environment env = Environment();
    Person p1 = Person(env);
    Person p2 = Person(env);
    p1.update();
    p2.update();
    env.update();
}
