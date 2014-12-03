#include "person.h"
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "speech.h"
#include "library.h"

int People::next_id = 0;

std::vector<Person*> People::people;

int People::get_next_id() {
    return ++next_id;
}

Person* People::get_person(const int _id) {
    try {
        return people.at(_id - 1); // IDs start at 1, so adjust for zero-indexing.
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Person ID out of range." << std::endl;
    }
    return nullptr;
}

std::vector<Person*>& People::get_people() {
    return people;
}

Person::Person(Environment &env, std::string n) : id(People::get_next_id()) {
    if (n.empty())
        name = "Person " + int_to_string(id);
    else
        name = n;
    mind = new Mind(this);    
    body = new Body(this, env);

    // Must be linked after construction, to ensure pointers are assigned correctly.
    mind->link_to_body(body);
    body->link_to_mind(mind);
    std::cout << get_name() << " is born." << std::endl;
    People::get_people().push_back(this);
}

Person::~Person() {
    delete mind;
    delete body;
}

std::string& Person::get_name() {
    return name;
}

int Person::get_id() const {
    return id;
}

void Person::update() {
    body->update();
    mind->update();
}
    