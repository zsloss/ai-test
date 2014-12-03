#include "body.h"
#include <iostream>

Body::Body(Person* _me, Mind*& _mind, Environment& env) : id(_me->get_id()), me(_me), mind(_mind), environment(&env) {

}

void Body::update() {
	listen();
	look();
}

void Body::eat() {
    hunger = 0;
    std::cout << me->get_name() << " eats." << std::endl;
}

void Body::listen() {
    // Get all surrounding speech.
    auto heard_speech = get_environment()->get_audio()->get_speech();
    // Inform the senses.
    mind->get_senses().rec_heard_speech(heard_speech);
}

void Body::look() {
    // Get all visible people.
    auto seen_people = get_environment()->get_visual()->get_people();

    // Inform the senses.
    mind->get_senses().rec_seen_people(seen_people);
}

void Body::greet(int tgt) {
    speak("greeting", "Howdy, " + People::get_person(tgt)->get_name() + "!", tgt);
}

void Body::speak(std::string category, std::string content, int tgt = -1) {
    Speech_packet* sp = new Speech_packet(id, category, content, tgt);
    get_environment()->get_audio()->add_speech(sp);
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
    std::cout << me->get_name() << " enters a new place..." << std::endl;
}
