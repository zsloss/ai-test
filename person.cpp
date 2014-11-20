#include "person.h"

/*
Rule: Only one non-const method is allowed to be public - the update() method.
*/

int Person::people = 0;

void Person::init() {
    id = ++people; 
    if (name.empty())
        name = "Person " + int_to_string(id);
    hunger = 0;
    std::cout << name << " is born." << std::endl;
}

Person::Person() {
    init();
}

Person::Person(std::string n) {
    name = n;
    init();
}

void Person::update() {
    hunger++;
    if (hunger > 75) inform("hungry");
}

void Person::inform(std::string msg) {
    if (msg == "hungry") {
        if (rnd_gen(1, 100) < hunger)
            eat();
    }
    else std::cerr << "Error: Unknown inform message" << std::endl;
}

void Person::inform(Person &p, std::string msg) {
    if (msg == "enters")
        greet(p);
    else if (msg == "greets") {
        if (interacting->id != p.id)
            greet(p);
    }
    else std::cerr << "Error: Unknown inform message" << std::endl;
}

void Person::eat() {
    hunger = 0;
    std::cout << name << " eats." << std::endl;
}

void Person::greet(Person &p) {
    std::cout << name << ": \"Hello, " << p.name << "!\"" << std::endl;
    interacting = &p;
    p.inform(*this, "greets");
}