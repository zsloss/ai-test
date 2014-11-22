#include "person.h"
#include <iostream>
#include <stdexcept>
#include "speech.h"
#include "library.h"

/*
Rule: Only one non-const method is allowed to be public - the update() method.
*/

int Person::next_id = 0;

std::vector<Person*> Person::people;

void Person::init() {
    
    if (name.empty())
        name = "Person " + int_to_string(id);
    hunger = 0;
    mind = new Mind(this);
    std::cout << name << " is born." << std::endl;
    people.push_back(this);
}

Person* Person::get_person(const int _id) {
    try {
        return people.at(_id);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Person ID out of range." << std::endl;
    }
    return nullptr;
}

int Person::get_id() const {
    return id;
}

Person::Person() : id(next_id++) {
    init();
}

Person::Person(std::string n) : id(next_id++) {
    name = n;
    init();
}

Person::~Person() {
    delete mind;
}

void Person::update() {
    hunger++;
    if (hunger > 75) inform("hungry");
    listen();
}

Environment* Person::get_environment() const {
    return environment;
}

void Person::set_environment(Environment &env) {
    environment = &env;
}

void Person::inform(std::string msg) {
    if (msg == "hungry") {
        if (rnd_gen(1, 100) < hunger)
            eat();
    }
    else std::cerr << "Error: Unknown inform message" << std::endl;
}

void Person::inform(int p_id, std::string msg) {
    if (msg == "enters")
        greet(p_id);
    else if (msg == "greets") {
        if (interacting != p_id)
            greet(p_id);
    }
    else std::cerr << "Error: Unknown inform message" << std::endl;
}

void Person::eat() {
    hunger = 0;
    std::cout << name << " eats." << std::endl;
}

void Person::listen() {
    auto all_speech = get_environment()->get_audio()->get_speech();
    std::vector<Speech_packet*> my_speech;  
    for (auto s: all_speech) {
        if (s->get_target_id() == id)
            my_speech.push_back(s);
    }
    for (auto s: my_speech) {
        int spk = s->get_speaker_id(); 
        if (s->get_category() == "greeting" && spk != interacting)
            greet(spk);
    }
}

void Person::greet(int tgt) {
    interacting = tgt;
    speak("greeting", "Howdy, " + get_person(tgt)->name + "!", tgt);
}

void Person::speak(std::string category, std::string content, int tgt = -1) {
    get_environment()->get_audio()->add_speech(new Speech_packet(id, category, content, tgt));
}
