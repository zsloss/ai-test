#include "mind.h"
#include <iostream>

Senses::Senses() {

}

Senses::~Senses() {

}

void Senses::rec_heard_speech(std::vector<Speech_packet*> &hs) {
	heard_speech = hs;
}

void Senses::rec_seen_people(std::unordered_set<int> &sp) {
	seen_people = sp;
}

std::vector<Speech_packet*>& Senses::get_heard_speech() {
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

int Action::get_priority() {
	return priority;
}

Mind::Mind(Person* _me, Body*& _body) : id(_me->get_id()), me(_me), body(_body) {
    
}

Senses& Mind::get_senses() {
	return senses;
}

void Mind::update() {
	plan();
}

void Mind::add_relation(int p_id) {
	relations.insert(std::pair<int, int>(p_id, 50));
}

bool Mind::knows(int p_id) {
	return relations.find(p_id) != relations.end();
}

void Mind::plan() {

    auto greeting = [&](int tgt) {
    	body->speak("greeting", "Howdy, " + People::get_person(tgt)->get_name() + "!", tgt);
    };

    // Loop over all visible people.
    for (auto s: get_senses().get_seen_people())
        if (!knows(s) && s != id)
        	actions.push_back(new Action([s, greeting](){greeting(s);}));

    // Store all speech directed to me.
    std::vector<Speech_packet*> my_speech;  
    for (auto s: get_senses().get_heard_speech()) {
        if (s->get_target_id() == id)
            my_speech.push_back(s);
    }

	// Loop over all speech directed to me.
    for (auto s: my_speech) {
        int spk = s->get_speaker_id();

        // If they are greeting me, greet them back.
        if (s->get_category() == "greeting" && knows(spk))
            body->greet(spk);
    }
}
