#include "person.h"
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "speech.h"
#include "library.h"

/*
Rule: Only one non-const method is allowed to be public - the update() method.
*/

int Person::next_id = 0;

std::vector<Person*> Person::people;

Person* Person::get_person(const int _id) {
    try {
        return people.at(_id - 1); // IDs start at 1, so adjust for zero-indexing.
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: Person ID out of range." << std::endl;
    }
    return nullptr;
}

int Person::get_id() const {
    return id;
}

Person::Person(std::string n) : id(++next_id) {
    if (n.empty())
        name = "Person " + int_to_string(id);
    else
        name = n;
    hunger = 0;
    mind = new Mind(this);
    std::cout << name << " is born." << std::endl;
    people.push_back(this);
}

Person::~Person() {
    delete mind;
}

void Person::update() {
    //hunger++;
    //if (hunger > 75) inform("hungry");
    listen();
    look();
}

Environment* Person::get_environment() const {
    return environment;
}

void Person::set_environment(Environment &env) {
    environment = &env;
}

void Person::eat() {
    hunger = 0;
    std::cout << name << " eats." << std::endl;
}

void Person::listen() {

    // Get all surrounding speech.
    auto heard_speech = get_environment()->get_audio()->get_speech();
    
    // Store all speech directed to me.
    std::vector<Speech_packet*> my_speech;  
    for (auto s: heard_speech) {
        if (s->get_target_id() == id)
            my_speech.push_back(s);
    }

    // Loop over all speech directed to me.
    for (auto s: my_speech) {
        int spk = s->get_speaker_id();

        // If they are greeting me, greet them back.
        if (s->get_category() == "greeting" && !mind->knows(spk))
            greet(spk);
    }
}

void Person::look() {

    // Get all visible people.
    auto seen_people = get_environment()->get_visual()->get_people();

    // Loop over all visible people.
    for (auto s: seen_people)
        if (!mind->knows(s) && s != id)
            greet(s);
}

void Person::greet(int tgt) {
    mind->add_relation(tgt);
    speak("greeting", "Howdy, " + get_person(tgt)->name + "!", tgt);
}

void Person::speak(std::string category, std::string content, int tgt = -1) {
    get_environment()->get_audio()->add_speech(new Speech_packet(id, category, content, tgt));
}

void Person::enter(Environment &env) {
    get_environment()->remove_person(id);
    set_environment(env);
    env.add_person(id);
    std::cout << name << " enters a new place..." << std::endl;
}
