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
    Environment testenv = Environment();
    Person p1 = Person("Matt");
    Person p2 = Person("Duncan");
    p1.set_environment(env);
    p2.set_environment(env);
    p1.enter(testenv);
    p2.enter(testenv);
    p1.update();
    p2.update();
    env.update();
}
