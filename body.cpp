#include "body.h"
#include <iostream>

Body::Body(Person* _me, Environment& env) : id(_me->get_id()), me(_me), next_action(nullptr) {
    set_environment(env);
}

Body::~Body() {
    delete next_action;
}

void Body::update() {
	listen();
	look();
}

void Body::listen() {
    // Get all surrounding speech.
    auto heard_speech = get_environment()->get_audio()->get_speech();

    // Inform the senses.
    mind().get_senses().rec_heard_speech(heard_speech);
}

void Body::look() {
    // Get all visible people.
    auto seen_people = get_environment()->get_visual()->get_people();
    // Remove myself from the set.
    seen_people.erase(id);
    // Inform the senses.
    mind().get_senses().rec_seen_people(seen_people);
}

void Body::speak(std::string category, std::string content, int tgt = -1) {
    get_environment()->get_audio()->add_speech(id, category, content, tgt);
}

void Body::set_next_action(const Action& act) {
    next_action = new Action(act);
}

Mind& Body::mind() {
    return me->get_mind(id);
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

void Body::execute_next_action() {
    if (next_action != nullptr)
        next_action->execute();

    // Action is complete and can be deleted.
    delete next_action; next_action = nullptr;
}
