#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "library.h"
#include "person.h"
#include "environment.h"

class Person;
class Environment;

int main(int argc, char* argv[]) {
    std::cout << "\n** AI TEST **\n" << std::endl;
    Environment env;

    std::vector<Person*> ppl;
    for (int i = 0; i < 5; i++)
       ppl.push_back(new Person(env));

    for (int i = 1; i <= 10; i++) {
    	std::cout << std::endl << "Cycle: " << i << std::endl << std::endl;
        for (auto p: ppl)
            p->update();
        for (auto p: ppl)
            p->act();
        env.update();
    }
}
