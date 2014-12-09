#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "person.h"
#include "environment.h"

class Person;
class Environment;

int main(int argc, char* argv[]) {
    std::cout << "\n** AI TEST **\n" << std::endl;
    Environment env;

    std::vector<std::shared_ptr<Person>> ppl;
    for (int i = 0; i < 5; i++)
        ppl.push_back(std::make_shared<Person>(env));

    for (int i = 1; i <= 10; i++) {
        std::cout << std::endl << "Cycle " << i << ":\n" << std::endl;
        for (auto p: ppl) {
            p->update();
            p->get_body(p->get_id()).get_environment()->update();
        }
    }
}
