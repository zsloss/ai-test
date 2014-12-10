#include "body.h"
#include <iostream>

Body::Body(Person* _me, Zone& z) : id(_me->get_id()), me(_me) {
    set_zone(z);
}

Body::~Body() {

}

void Body::update() {
	listen();
	look();
}

void Body::listen() {
    // Get all surrounding speech.
    auto heard_speech = zone->get_environment().get_speech();

    // Inform the senses.
    mind().get_senses().rec_heard_speech(heard_speech);
}

void Body::look() {
    // Get all visible people.
    auto seen_people = zone->get_environment().get_people();
    // Remove myself from the set.
    seen_people.erase(id);
    // Inform the senses.
    mind().get_senses().rec_seen_people(seen_people);
}

void Body::speak(std::string category, std::string content, int tgt = -1) {
    zone->get_environment().add_speech(id, category, content, tgt);
}

void Body::set_next_action(const Action& act) {
    next_action.reset(new Action(act));
}

Mind& Body::mind() {
    return me->get_mind(id);
}

Zone* Body::get_zone() const {
    return zone;
}

void Body::set_zone(Zone &z) {
    zone = &z;
    zone->add_person(id);
}

void Body::enter(Zone &z) {
    get_zone()->remove_person(id);
    set_zone(z);
    std::cout << me->get_name() << " enters a new place..." << std::endl;
}

void Body::execute_next_action() {
    if (next_action != nullptr)
        next_action->execute();
    else
        std::cerr << "WARNING: " << id << " has no action to execute." << std::endl;

    // Action is complete and can be deleted.
    next_action.reset();
}
