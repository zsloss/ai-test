#include "body.h"
#include <iostream>

Body::Body(Person* _me, Mind* _mind, Environment &env) : id(_me->get_id()) {
    me = _me;
    mind = _mind;
    set_environment(env);
    hunger = 0;
}

void Body::update() {
	listen();
	look();
}

void Body::eat() {
    hunger = 0;
    std::cout << me->name << " eats." << std::endl;
}

void Body::listen() {

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

void Body::look() {

    // Get all visible people.
    auto seen_people = get_environment()->get_visual()->get_people();

    // Loop over all visible people.
    for (auto s: seen_people)
        if (!mind->knows(s) && s != id)
            greet(s);
}

void Body::greet(int tgt) {
    mind->add_relation(tgt);
    speak("greeting", "Howdy, " + People::get_person(tgt)->name + "!", tgt);
}

void Body::speak(std::string category, std::string content, int tgt = -1) {
    get_environment()->get_audio()->add_speech(new Speech_packet(id, category, content, tgt));
}

Environment* Body::get_environment() const {
    return environment;
}

void Body::set_environment(Environment &env) {
    environment = &env;
    env.add_person(id);
}

void Body::enter(Environment &env) {
    get_environment()->remove_person(id);
    set_environment(env);
    std::cout << me->name << " enters a new place..." << std::endl;
}