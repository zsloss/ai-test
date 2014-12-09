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

std::string People::get_name(const int _id) {
    auto p = get_person(_id);
    return p ? p->get_name() : "ERROR: Unable to get name.";
}

Person* People::get_person(const int _id) {
    try {
        return people.at(_id - 1); // IDs start at 1, so adjust for zero-indexing.
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Person ID (" << _id << ") out of range." << std::endl;
    }
    return nullptr;
}

std::vector<Person*>& People::get_people() {
    return people;
}

int People::num_active() {
    return people.size();
}

Person::Person(Environment &env, std::string n) : id(People::get_next_id()) {
    if (n.empty())
        name = "Person " + int_to_string(id);
    else
        name = n;
    // mind = std::make_unique<Mind>(this);    
    // body = std::make_unique<Body>(this, env);
    mind = std::unique_ptr<Mind>(new Mind(this));
    body = std::unique_ptr<Body>(new Body(this, env));

    std::cout << get_name() << " is born." << std::endl;
    People::get_people().push_back(this);
}

Person::~Person() {
    std::cout << id << " dies" << std::endl;
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
    body->execute_next_action();  
}
    
Mind& Person::get_mind(int _id) {
    if (id != _id)
        std::cerr << "WARNING: UNAUTHORISED ACCESS OF MIND ID: " << id << " BY ID: " << _id << std::endl;
    return *mind;
}

Body& Person::get_body(int _id) {
    if (id != _id)
        std::cerr << "WARNING: UNAUTHORISED ACCESS OF BODY ID: " << id << " BY ID: " << _id << std::endl;
    return *body;
}
