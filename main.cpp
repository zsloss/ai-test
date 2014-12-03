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
    Environment env;
    Person p1(env);
    Person p2(env);
    p1.update();
    p2.update();
    env.update();
}
