#include "mind.h"
#include <iostream>
#include <algorithm>
#include <iterator>

Senses::Senses() {

}

Senses::~Senses() {

}

void Senses::rec_heard_speech(std::vector<Speech_packet> &hs) {
	heard_speech = hs;
}

void Senses::rec_seen_people(std::unordered_set<int> &sp) {
	seen_people = sp;
}

std::vector<Speech_packet>& Senses::get_heard_speech() {
	return heard_speech;
}

std::unordered_set<int>& Senses::get_seen_people() {
	return seen_people;
}

Action::Action(std::function<void()> _act) {
    act = _act;
}

void Action::execute() {
    act();
}

int Action::get_priority() const {
	return priority;
}

bool Action::operator < (const Action& rhs) const {
    return get_priority() < rhs.get_priority();
}

Mind::Mind(Person* _me) : id(_me->get_id()), me(_me) {
    
}

Senses& Mind::get_senses() {
	return senses;
}

void Mind::update() {
	plan();
    make_decision();
}

Body& Mind::body() {
    return me->get_body(id);    
}

void Mind::add_relation(int p_id) {
	relations.insert(std::pair<int, int>(p_id, 50));
}

bool Mind::knows(int p_id) {
	return relations.find(p_id) != relations.end();
}

void Mind::plan() {

    auto greeting = [&](int tgt) {
    	body().speak("greeting", "Howdy, " + People::get_name(tgt) + "!", tgt);
        add_relation(tgt);
    };

    // Loop over all visible people.
    for (auto s: get_senses().get_seen_people())
        if (!knows(s)) {
        	actions.emplace_back([s, greeting](){greeting(s);});
        }

    // Store all speech directed to me.    
    auto heard_speech = get_senses().get_heard_speech();
    std::vector<Speech_packet> my_speech;  
    auto to_me = [&](Speech_packet &s){return s.get_target_id() == id;};
    std::copy_if(heard_speech.begin(), heard_speech.end(), std::back_inserter(my_speech), to_me);

	// Loop over all speech directed to me.
    for (auto &s: my_speech) {
        int spk = s.get_speaker_id();
        // If they are greeting me, greet them back.
        if (!knows(spk) && s.get_category() == "greeting") {
        	actions.emplace_back([spk, greeting](){greeting(spk);});
        }
    }
}

void Mind::make_decision() {
    // Find the action with the highest priority.
    auto act = std::max_element(actions.begin(), actions.end());

    // Unless there are no actions at all, copy winning Action to body.
    if (act != actions.end())
        body().set_next_action(*act);

    // Clear the actions collection.
    actions.clear();
}
