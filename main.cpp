#include <iostream>
#include <string>
#include <vector>
#include "library.h"

class Person {
    public:
        int hunger;
        std::string name;
        Person();
        Person(std::string);
        void update();
        void inform(std::string);
        void inform(Person&, std::string);
        void eat();
        void greet(Person&);
    private:
        static int people;
        int id;
        void init();
        Person *interacting;
};

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

int main(int argc, char* argv[]) {
    std::cout << "** AI TEST **" << std::endl << std::endl;
    Person p1 = Person();
    for (int i = 0; i < 100; i++)
        p1.update();
    Person p2 = Person();
    p1.inform(p2, "enters");
    std::vector<Person> people = {Person(), Person()};
}


