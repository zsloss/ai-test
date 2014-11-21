#include <iostream>
#include <string>
#include <vector>
#include "library.h"
#include "person.h"
#include "environment.h"

int main(int argc, char* argv[]) {
    std::cout << "\n** AI TEST **\n" << std::endl;
    Environment env = Environment();
    Person p1 = Person();
    Person p2 = Person();
    p1.set_environment(env);
    p2.set_environment(env);
    p1.inform(p2, "enters");
    env.update();
}
